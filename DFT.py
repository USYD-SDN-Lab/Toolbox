import numpy as np


class DFT:
    '''
    constructor
    @size:          the size of discrete Fourier transform
    @extra_dims:    the extra dimensions (a tuple recording the other dimensions 
                    except the last two, which should size x size). If you give fractional
                    numbers, they will be transformed into integers by numpy
    '''
    def __init__(self, size, *, extra_dims = ()):
        # record the size of (I)DFT matrices
        try:
            self.size = np.asarray(size);
            if self.size.ndim != 0:
                raise Exception("The input size must be a scalar.");
        except:
            raise Exception("The input size must be a scalar.");
            
        # calculate the shape of (I)DFT matrices
        if not isinstance(extra_dims, tuple):
            raise Exception("The extra dimension must be a tuple");
        else:
            try:
                extra_dims = np.asarray(extra_dims, dtype=np.dtype(int));
                if extra_dims.ndim != 1:
                    raise Exception("The extra dimension must be an 1-D tuple");
                else:
                    self.shape = np.append(extra_dims, [1,1]);
            except:
                raise Exception("The extra dimension must be an 1-D tuple");
        
    '''
    generate the DFT matrix
    '''            
    def gen_dft_mat(self):
        Wn = np.exp(-1j*2*np.pi/self.size);        
        colVec = np.expand_dims(np.arange(0, self.size), 0).T;
        rowVec = np.expand_dims(np.arange(0, self.size), 0);
        dftmat = np.power(Wn, np.matmul(colVec, rowVec));
        dftmat_norm = 1/np.sqrt(self.size)*dftmat;
        # fit other dimensions
        return np.tile(dftmat_norm, self.shape);
        
    '''
    generate the IDFT matrix
    '''
    def gen_idft_mat(self):
        Wn = np.exp(1j*2*np.pi/self.size);
        colVec = np.expand_dims(np.arange(0, self.size), 0).T;
        rowVec = np.expand_dims(np.arange(0, self.size), 0);
        idftmat = np.power(Wn, np.matmul(colVec, rowVec));
        idftmat_norm = 1/np.sqrt(self.size)*idftmat;
        # fit other dimensions
        return np.tile(idftmat_norm, self.shape);