# AssetPacks

AssetPacks have a set structure that must be strictly followed:

```tree
.
├── assetpack
│   ├── properties.json
│   └── res
│       ├── font
│       │   └── GPixel_v1.0.0.ttf
│       ├── img
│       │   ├── background
│       │   │   └── backgroundMaster-0001.png
│       │   ├── bar
│       │   │   └── timerBar-0001.png
│       │   ├── board
│       │   │   └── boardMaster-0001.png
│       │   ├── character
│       │   │   └── teacherMaster-0001.png
│       │   ├── misc
│       │   │   └── correctnessIndicator-0001.png
│       │   ├── notepad
│       │   │   └── notepadMaster-0001.png
│       │   └── splash
│       │       └── splashMaster-0001.png
│       └── sfx
│           ├── music
│           │   └── mainMaster-0001.ogg
│           └── splashMaster-0001.ogg
```

All files need to be present, or else the program will either not render the
missing texture, not play any noise or it will crash if no font is present. The
properties.json file is required to be present, because if the program cannot
detect it, it will not use the AssetPack.

The textures can be any size, but they will be resized to the **proportions** of
the original textures. The `properties.json` file can be empty, but it is
recommended to include metadata about the AssetPack. If metadata should be
included, the file structure of `properites.json` should be this:

```json
[
  {
    "AssetPack": {
      "Name": "Name",
      "Description": "Description",
      "Version": "x.x.x" // For what version was the AssetPack made
    }
  }
]
```
