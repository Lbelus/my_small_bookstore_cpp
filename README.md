# take_home_randstad_01


## Installation

### Step 1. setup the Environment.
Using docker, from the ``project root`` dir.
- Build the image:
```bash
docker build -t img_th_ran .
```


- Run the container:
```bash
docker run -it -v /pathToDir/:/workspace/ --name cont_th_ran img_th_ran /bin/bash
```

