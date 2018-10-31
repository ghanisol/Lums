"use strict"

const fs = require('fs')
const http = require('http')
const https = require('https')
const parse5 = require('parse5')
const urllib = require('url')

const delay = msecs => new Promise(resolve => setTimeout(resolve, msecs))

const readFile = file => new Promise( (resolve, reject) =>
	fs.readFile(file, 'utf8', (err, data) => err ? reject(err) : resolve(data)))

const readJSON = file => readFile(file).then(JSON.parse)

const fetchURL = url => new Promise( (resolve, reject) => {
	if (url.startsWith('http://'))
		http.get(url, res => resolve(res)).on('error', e => reject(e))
	else if (url.startsWith('https://'))
		https.get(url, res => resolve(res)).on('error', e => reject(e))
})

const parseResponse = (res, url) => {
	const parser = new parse5.SAXParser()
	const _url = urllib.parse(url)

	parser.on('startTag', (tag, attr, isSC) => { 

		if (configs.maxRequests && tag === 'a')
		{
			attr.forEach(a => {
				if (a.name === 'href')
				{
					if (a.value.startsWith('//'))
						crawlUrl(_url.protocol + a.value, url)
					else if (a.value.startsWith('/'))
						crawlUrl(_url.href + a.value, url)
					else if ((a.value.startsWith('http://')) || (a.value.startsWith('https://')))
						crawlUrl(a.value, url)
				}
			})
		}
	});

	res.pipe(parser)
}

// Recursively crawl the urls found
const crawlUrl = (url, fromUrl) => {

	const url_ = urllib.parse(url)
	
	if (!(url_.hostname in siteInfo))
	{
		siteInfo[url_.hostname] = {requestCount : 0, inLinks: [], outLinks: [], promisedDelay : undefined}

		siteInfo[url_.hostname].promisedDelay = fetchURL(url)
		.then(res => parseResponse(res, url))
		.then(delay(configs.minFetchInterval))
		.catch((e) => console.log(e))
		
		siteInfo[url_.hostname].requestCount++

		updateLinks(url, fromUrl)

		--configs.maxRequests || printCrawlInfo()
	}
	else
	{
		if (siteInfo[url_.hostname].requestCount < configs.maxRequestsPerSite)
		{
			siteInfo[url_.hostname].promisedDelay = siteInfo[url_.hostname].promisedDelay
												.then(fetchURL(url)
												.then(res => parseResponse(res, url))
												.then(delay(configs.minFetchInterval)))
												.catch((e) => console.log(e))

			siteInfo[url_.hostname].requestCount++

			updateLinks(url, fromUrl)

			--configs.maxRequests || printCrawlInfo()	
		}
			
	}
}

// Updates inLinks, and outLinks for the urls in siteInfo
const updateLinks = (url, fromUrl) => {
	if (fromUrl !== null)
	{
		const url_ = urllib.parse(url)
		const fromUrl_ = urllib.parse(fromUrl)

		if (fromUrl_.hostname !== url_.hostname)
		{
			if (siteInfo[url_.hostname].inLinks.indexOf(fromUrl_.hostname) === -1)
			{
				siteInfo[url_.hostname].inLinks.push(fromUrl_.hostname)	
			}

			if (siteInfo[fromUrl_.hostname].outLinks.indexOf(url_.hostname) === -1)
			{
				siteInfo[fromUrl_.hostname].outLinks.push(url_.hostname)	
			}	
		}
			
	}
}

// outLinks = Number of distinct domains visited from a particular link, not the links found.
const printCrawlInfo = () => {
	for (let key in siteInfo)
	{
		console.log('\ndomain : ' + key)
		console.log('Request Count : ' + siteInfo[key].requestCount)
		console.log('inLinks Count : ' + siteInfo[key].inLinks.length)
		console.log('outLinks Count : ' + siteInfo[key].outLinks.length)
	}
}

let siteInfo = {}
let configs = {}

readJSON('config.json')
.then(data => {
	configs = data
	configs.initialUrls.forEach(url => crawlUrl(url, null))
}).catch((e) => console.log(e))