classdef HardDetection < handle
    properties
        symbool_pool
    end
    
    methods
        % constructor
        % @symbool_pool: the constellation map
        function self = HardDetection(symbool_pool)
            % type check
            if ~isvector(symbool_pool)
                error("The constellation map (symbool_pool) must be a vector");
            end
            
            % assign
            if isrow(symbool_pool)
                symbool_pool = symbool_pool.';
            end
            self.symbool_pool = symbool_pool;
        end
        
        % hard detect
        % detect
        
    end
end