# Toolbox
Useful toolboxes for any project
* **In another local repositiory, add this module**
```sh
git submodule add git@github.com:USYD-Center-of-Telecom-and-IoT/Toolbox.git Modules/Toolbox
```
Now, you can see a folder `Modules` with `Toolbox` inside
* **import this module**
	* Matlab
	```
	addpath("Modules/Toolbox");
	```
	* Python
	```
	if '.' not in __name__ :
		from Modules.Toolbox.[file name]  import [class name]
	else:
		from .Modules.Toolbox.[file name] import [class name]
	```

## DFT
This class generates DFT(IDFT) matrices.
* constructor<br>
`@size`: the size of DFT(IDFT) matrices. <br>
`@extra_dims`(only for **Python**): is a tuple recording the other dimensions except the last two, which should be `size by size`). If you give fractional numbers, they will be transformed into integers by numpy.
* gen_dft_mat<br>
generate the DFT matrix
* gen_idft_mat<br>
generate the IDFT matrix