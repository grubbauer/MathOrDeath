# MathOrDeath's Modules

## AssetPacks (assetpacks.h)

### Functions

#### checkForAssetpack

Checks if AssetPack's `properties.json` file is present at
`%APPDATA%/MathOrDeath/assetpack`. Will return `false` (`0`) if file is not
present and `true` (`1`) if file exists.

USAGE:

```cpp
grubbauer::checkForAssetpack()
```

## Equation (equation.h)

### Functions

#### getRandomEquation

Generates a random equation based on a standart value, which acts as a basepoint
to generate the equation. The formula for the range of the equation is
following:

$\text{range} = 1 \cdots \left(\text{givenrange} \times 2\right)$

The equation will then be generated in this format:

`number1 operator number2`
e.g.
`42 + 137`

Four possible types of math questions are possible:

* Addition
* Subtraction
* Multiplication
* Division

USAGE:

```cpp
grubbauer::getRandomEquation(int max)
```

### getEquationAnswer

Solves the question and returns the result as a float. The function use a
stringstream to extrude the numbers and the operator. It then calculates the
equation and returns the result.

e.g.:

Equation: `42 + 137`
Result: `179`

USAGE:

```cpp
grubbauer::getEquationAnswer(std::string equation)
```

## Random (random.h)

### Functions

#### randomNum

Generates a random number within a given range. Uses the 32-bit Mersenne
Twister.

USAGE:

```cpp
grubbauer::randomNum(int min, int max)
```

## SaveFile (savefile.h)

### Functions

#### readSaveFile

Reads over the SaveFile located at `%APPDATA%/MathOrDeath/saveFile.json` and
loops over its content. It then uses the highest score and returns it.

Example:
Scores:
`[{"Level": 42}, {"Level": 137}]`
Highest Score: `137`

USAGE:

```cpp
grubbauer::readSaveFile()
```

### saveSaveFile

Creates a SaveFile if none exists at `%APPDATA%/MathOrDeath/saveFile.json` and
writes a provided value as a JSON value to the SaveFile.

USAGE:

```cpp
grubbauer::saveSaveFile(int lvl);
```
