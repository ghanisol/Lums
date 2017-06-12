const appid = '939603670c92440a2e36f9cfa2436ab8';
const url = 'http://api.openweathermap.org/data/2.5/weather?units=metric';
let temp = 0;
let city = '';

async function handleSubmit(event) {
    
    event.preventDefault();
    const resp = await fetch(`${url}&appid=${appid}&q=${city}`);
    const data = await resp.json();
    temp = data.main.temp;
    redraw();

}
function redraw() {
    ReactDOM.render(React.createElement("form", { onSubmit: handleSubmit },
        React.createElement("input", {
            type: 'text',
            onChange: ev => city = ev.target.value
        }),
        React.createElement("input", {
            type: 'submit',
            value: 'Go get temperature'
        }),
        React.createElement("h2", null, "Temperature is ${temp}")),
        document.getElementById('root'));
}
redraw();
