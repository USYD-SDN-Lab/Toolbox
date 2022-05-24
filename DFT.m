classdef DFT < handle
    properties
        size {mustBeInteger}
    end
    methods
        % constructor
        % @size: the size of discrete Fourier transform
        function self = DFT(size)
            if isscalar(size)
                self.size = size;
            else
                error("The discrete Fourier transform size must be a scalar.");
            end
        end
        
        % generate the DFT matrix
        function mat_dft = gen_dft_mat(self)
            Wn = exp(-1j*2*pi/self.size);
            mat_dft = 1/sqrt(self.size)*Wn.^((0:self.size-1)'*(0:self.size-1));
        end
        
        % generate the IDFT matrix
        function mat_idft = gen_idft_mat(self)
            Wn = exp(1j*2*pi/self.size);
            mat_idft = 1/sqrt(self.size)*Wn.^((0:self.size-1)'*(0:self.size-1));
        end
    end
end