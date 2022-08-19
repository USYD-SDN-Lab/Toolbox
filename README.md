# Toolbox
![GPLv3](https://www.gnu.org/graphics/gplv3-or-later-sm.png)<br>
Useful toolboxes for any project<br>
This project is under the GNU General Public License v3.0. If you include this repository, you will have to share your codes publicly.
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

## Classes
### DFT
This class generates DFT(IDFT) matrices.
* DFT(size) or DFT(size, extra_dims=)<br>
`@size`: the size of DFT(IDFT) matrices. <br>
`@extra_dims`(only for **Python**): is a tuple recording the other dimensions except the last two, which should be `size by size`). If you give fractional numbers, they will be transformed into integers by numpy.
* gen_dft_mat()<br>
generate the DFT matrix
* gen_idft_mat()<br>
generate the IDFT matrix

### MatOps
* transpose(dim1, dim2)<br>
`@dim1`: the 1st dimension to transpose (starting from 1, the last dimension is -1)<br>
`@dim2`: the 2nd dimension to transpose (starting from 1, the last dimension is -1)<br>
