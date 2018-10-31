#!/usr/bin/env python

from mrjob.job import MRJob
from mrjob.step import MRStep
from sys import *
import os

rankDiff = [1]

class socialRank_init(MRJob):
	
	def init_mapper(self, _, line):
		data = line.split()
		yield data[0], data[1]
			

	def init_reducer(self, userid, friendList):
		friends = []
		for friend in friendList:
			friends.append(str(friend))

		output_str = userid + ",1," + ",".join(friends) + ",0"
		yield None, output_str

	def steps(self):
		return [
            MRStep(mapper=self.init_mapper,
                   reducer=self.init_reducer)
        ]

class socialRank_iter(MRJob):

	global rankDiff

	def iter_mapper(self, _, line):
		data = line.split()
		
		value = data[1].strip('"')
		value = value.split(",")
		
		userid = value[0]
		rank = float(value[1])
		prev_rank = value[len(value)-1]
		friends = value[2:len(value)-1]

		friendCount = len(friends)
		
		if (friendCount > 0):
			net_rank = rank / friendCount
		else:
			net_rank = 0	
		

		prev_rank = str(rank)
		

		for friend in friends:
			yield friend, net_rank
		yield userid, friends
		yield userid, prev_rank
	
	def iter_reducer(self, userid, rank_friendlist):
		ranks = []
		friend_list = []
		prev_rank = 0
		for data in rank_friendlist:
			if (isinstance(data, list) == True):
				friend_list += data
			elif (isinstance(data, str) == True):
				prev_rank = data
			else:
				ranks.append(data)

		net_rank = sum(ranks)
		net_rank = 0.15 + 0.85 * net_rank


		rankDiff.append(abs(net_rank - float(prev_rank)))

		output_str = userid + "," + str(net_rank) + "," + ",".join(friend_list) + "," + str(prev_rank)
		yield None, output_str

	def steps(self):
		return [
        	MRStep(mapper=self.iter_mapper,
                   reducer=self.iter_reducer)
        ]

class socialRank_final(MRJob):
	
	def finish_mapper(self, _, line):
		data = line.split()
		value = data[1].strip('"')
		value = value.split(",")
		
		userid = value[0]
		rank = float(value[1])

		yield rank, userid

	def finish_reducer(self, rank, userids):
		users = []
		for user in userids:
			users.append(user)
		if not users[0] == "" :
			yield rank, users

	def steps(self):
		return [
        	MRStep(mapper=self.finish_mapper,
                   reducer=self.finish_reducer)
        ]
if __name__ == '__main__':

	input_Dir = argv[1]
	output_Dir = argv[2]
	cmd = ['-r', 'inline', input_Dir, '-o', output_Dir]
    
	job = socialRank_init(cmd)

	with job.make_runner() as runner:
		runner.run()
	
	cmd[2] = cmd[4]
	
	while (max(rankDiff) > 0.01):
		
		rankDiff = []
		job = socialRank_iter(cmd)
		with job.make_runner() as runner:
			runner.run()
		

	job = socialRank_final(cmd)
	with job.make_runner() as runner:
		runner.run()
  	

	output_path = "./output/"
	output_file_list = os.listdir(output_path)

	output_file_list = output_file_list[len(output_file_list)-2 : len(output_file_list)]

	file1 = []
	with open(output_path + output_file_list[1], 'rb') as f:
		data = f.readline()
		while (data):
			file1.append(data) 
			data = f.readline()

	file2 = []
	with open(output_path + output_file_list[0], 'rb') as f:
		data = f.readline()
		while (data):
			file2.append(data) 
			data = f.readline()

	file1 = file1[::-1]
	file2 = file2[::-1]

	with open(output_path + 'res.txt', 'a+') as f:
		for i in file1:
			f.write(i)
		for i in file2:
			f.write(i)

	result = ['res.txt']
	del_list = [x for x in os.listdir(output_path) if not x in result]

	for i in del_list:
		os.remove(output_path + i)

