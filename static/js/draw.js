const shuffleArray = array => {
    for (let i = array.length - 1; i > 0; i--) {
        const j = Math.floor(Math.random() * (i + 1));
        const temp = array[i];
        array[i] = array[j];
        array[j] = temp;
    }
    return array
}

document.querySelector('#generate').addEventListener('click', () => {
    const inputFields = document.querySelectorAll('input.generateInput')
    const values = {}
    for (field of inputFields) {
        values[field.name] = field.value
    }
    const numbers = shuffleArray([...Array(values.generateMax - values.generateMin).keys()])
    document.querySelector('#numbers').value = numbers.join(' ')
})

document.querySelector('#visualize').addEventListener('click', () => {
    const numbers = document.querySelector('#numbers').value
    const params = [['numbers', numbers]]
    const url = `/pushswap?${new URLSearchParams(params).toString()}`;
    fetch(url).then((res) => res.json()).then(cmds => console.log(cmds))
})