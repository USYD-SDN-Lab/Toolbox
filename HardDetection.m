classdef HardDetection < handle
    properties
        symbol_pool     % a row vector of the constellation map
    end
    
    methods
        % constructor
        % @symbool_pool: a vector of the constellation map
        function self = HardDetection(symbol_pool)
            % type check
            if ~isvector(symbol_pool)
                error("The constellation map (symbool_pool) must be a vector");
            end
            
            % transpose `symbol_pool` into a column vector & assign
            if ~isrow(symbol_pool)
                symbol_pool = symbol_pool.';
            end
            self.symbol_pool = symbol_pool;
        end
        
        % hard estimate
        % @syms:                    a vector the received symbols
        % @origin_syms:             the original symbols (if give, ouput the ser)
        % @origin_syms_ids:         the original symbol Ids (if give, ouput the ser)
        function out = estim(self, syms)
            % type check & transpose `syms` into a column vector
            if ~isvector(syms)
                error("The symbols to detect must be a vector.");
            end
            if ~iscolumn(syms)
                syms = syms.';
            end

            % detect
            syms_dist = abs(syms - self.symbol_pool).^2;                % calculate the minima distance
            [~, min_syms_dist_inds] =  min(syms_dist,[],2);             % Obtain indices of minimum ecludian distance
            out = self.symbol_pool(min_syms_dist_inds);                 % Obtain symbols of minimum ecludian distance
        end
        
        % hard detect 
    end
end