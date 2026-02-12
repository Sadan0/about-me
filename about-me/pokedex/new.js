let pokemonArray; 
let pokeCount = null;
const photoDiv = document.querySelector("#poke-photo");
const nameDiv = document.querySelector('#poke-name');
const type1 = document.querySelector('#poke-type1');
const type2 = document.querySelector('#poke-type2');

async function getPokimonArray(){
  try{
    
    const fullArray = await fetch(`https://pokeapi.co/api/v2/pokemon/?offset=0&limit=1302`);

    if(!fullArray.ok){
      throw new Error(`pokemon Array error`);
    }
    const data = await fullArray.json();
    pokemonArray = data.results;
    pokeCount = data.count;
    console.log(pokemonArray);

  }catch(error){
    console.error('error fectching array data: ', error);
  }
}

let currentPokemonidx = 0;
let nextButton = document.querySelector("#poke-next-button");
let backButton = document.querySelector('#poke-back-button');

function handleNextClick(){
  nextButton.addEventListener("click", () => {
    if(currentPokemonidx < pokeCount){
      currentPokemonidx = currentPokemonidx + 1;
      updatePokedex();
    }
  });
}

function handleBackClick(){
  backButton.addEventListener("click", () => {
    if(currentPokemonidx > 0){
      currentPokemonidx = currentPokemonidx - 1;
      updatePokedex();
    }
  });
};

function getColor(type){
  const pokemonTypeColors = {
    normal: "#A8A77A",
    fire: "#EE8130",
    water: "#6390F0",
    electric: "#F7D02C",
    grass: "#7AC74C",
    ice: "#96D9D6",
    fighting: "#C22E28",
    poison: "#A33EA1",
    ground: "#E2BF65",
    flying: "#A98FF3",
    psychic: "#F95587",
    bug: "#A6B91A",
    rock: "#B6A136",
    ghost: "#735797",
    dragon: "#6F35FC",
    dark: "#705746",
    steel: "#B7B7CE",
    fairy: "#D685AD",
  };
  return pokemonTypeColors[type]

}

async function updatePokedex(){

  once = false;

  // pokemon photo update
  let url = `https://pokeapi.co/api/v2/pokemon/${currentPokemonidx}`;
  let pokeTypeData = await fetch(url);
  let pokeType = await pokeTypeData.json();
  photoDiv.style.backgroundImage= `url('${pokeType.sprites.front_default}')`;

  // pokemon name update
  let pokename = pokeType.name.toUpperCase();
  nameDiv.textContent = `${pokename}`;


  // type update
  let type1Info = pokeType.types[0].type.name;
  let type2Info = pokeType.types[1].type.name;

  type1.textContent = `${type1Info.toUpperCase()}`;
  type1.style.backgroundColor = getColor(type1Info);
  if (type2Info !=  undefined){
    type2.textContent = `${type2Info.toUpperCase()}`;
    type2.style.backgroundColor = getColor(type2Info);
  }

}

let once = true;

function pokedexOn(){
  once? updatePokedex(): null;
  if(pokeCount !==  null){
    handleNextClick();
    handleBackClick();
    return
  }
  requestAnimationFrame(pokedexOn);
};


getPokimonArray();
requestAnimationFrame(pokedexOn);

