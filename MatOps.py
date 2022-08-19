import numpy as np;
import torch;

class MatOps:
    
    mat = None;
    
    '''
    constructor
    @mat: the matrix to be operated
    '''
    def __init__(self, mat):
        if isinstance(mat, np.ndarray):
            pass;
        elif isinstance(mat, torch.Tensor):
           pass;
        else:
            try:
                mat =  np.asarray(mat);
            except:
                raise Exception("Wrong Data Type.");
        self.mat = mat;
        
    '''
    transpose
    @dim1: the 1st dimension to transpose (starting from 1, the last dimension is -1)
    @dim2: the 2nd dimension to transpose (starting from 1, the last dimension is -1)
    '''
    def transpose(self, dim1, dim2):
        if dim1 > self.mat.ndim:
            raise Exception("1st transpose dimensions are out of the boundary.");
        if dim2 > self.mat.ndim:
            raise Exception("2nd transpose dimensions are out of the boundary.");
        
        if dim1 > 0:
            dim1 = dim1 - 1;
        if dim2 > 0:
            dim2 = dim2 - 1;
        
        if isinstance(self.mat, np.ndarray):
            mat_transpose_seq = list(range(self.mat.ndim));
            tmp = mat_transpose_seq[dim1];
            mat_transpose_seq[dim1] = mat_transpose_seq[dim2];
            mat_transpose_seq[dim2] = tmp;
            return self.mat.transpose(mat_transpose_seq);
        if isinstance(self.mat, torch.Tensor):
            return torch.transpose(self.mat, dim1-1, dim2-1);
        