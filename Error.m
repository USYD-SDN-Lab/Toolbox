classdef Error < handle
    properties(Constant)
        TOOLBOX_ERR_STR_MAX_LEN         = 1024;		% the maximal length for a string
        TOOLBOX_ERR_ILLEGAL_PARAMETERS  = 400;      % error - illegal parameters
        TOOLBOX_ERR_MEMORY_SHORTAGE     = 406;      % error - not enough memory
        TOOLBOX_ERR_INTERNAL            = 500;      % error - cannot create this exception
    end
    properties
        code {mustBeInteger}    = 0;
        loc {mustBeText}        = "";
        msg {mustBeText}        = "";
    end
    methods
        % Constructor
        % @code:            the code
        % @pathprefix:      the path prefix (NULL for root files)
        % @filename:		the name of the file
        % @classname:		the classname
        % @methodname:		the method/function name
        % @msg:             the message
        function self = Error(varargin)
            % optional inputs: name-value pairs
            inPar = inputParser;
            % Set default values                                            % the default is not decoding
            % Register names
            addParameter(inPar, 'code',         self.code,  @(x) isnumeric(x));   
            addParameter(inPar, 'pathprefix',   "",         @(x) isvector(x)&&ischar(x)||isscalar(x)&&isstring(x));   
            addParameter(inPar, 'filename',     "",         @(x) isvector(x)&&ischar(x)||isscalar(x)&&isstring(x));   
            addParameter(inPar, 'classname',    "",         @(x) isvector(x)&&ischar(x)||isscalar(x)&&isstring(x));
            addParameter(inPar, 'methodname',   "",         @(x) isvector(x)&&ischar(x)||isscalar(x)&&isstring(x)); 
            addParameter(inPar, 'msg',          self.msg,   @(x) isvector(x)&&ischar(x)||isscalar(x)&&isstring(x)); 
            inPar.KeepUnmatched = true;                                     % Allow unmatched cases
            inPar.CaseSensitive = false;                                    % Allow capital or small characters
            parse(inPar, varargin{:});                                      % Try to load those inputs 
            % set code
            self.code = inPar.Results.code;
            % set loc - format check
            needPathSeparator = ~endsWith(inPar.Results.pathprefix, '/');
            needSpace = inPar.Results.classname ~= "" || inPar.Results.methodname ~= "";
            needClassMethodSeparator = inPar.Results.classname ~= "" && inPar.Results.methodname ~= "";
            needMethodParentheses = inPar.Results.methodname~="" && ~matches(inPar.Results.methodname, asManyOfPattern(alphanumericsPattern(1), 1) + ("("|")"|"()"));
            % set loc - copy
            if inPar.Results.pathprefix ~= ""
                self.loc = inPar.Results.pathprefix;
            end
            if needPathSeparator
                self.loc = self.loc + '/';
            end
            if inPar.Results.filename ~= ""
                self.loc = self.loc + inPar.Results.filename;
            end
            if needSpace
                self.loc = self.loc + ' ';
            end
            if inPar.Results.classname ~= ""
                self.loc = self.loc + inPar.Results.classname;
            end
            if needClassMethodSeparator
                self.loc = self.loc + '::';
            end
            if inPar.Results.methodname ~= ""
                self.loc = self.loc + inPar.Results.methodname;
            end
            if needMethodParentheses
                self.loc = self.loc + '()';
            end
            
            % set msg
            self.msg = inPar.Results.msg;
        end
        
        % Set Types
        function SetType2IllegalParameters(self)
            self.code = Error.TOOLBOX_ERR_ILLEGAL_PARAMETERS;
        end
        function SetType2MemoryShortage(self)
            self.code = Error.TOOLBOX_ERR_MEMORY_SHORTAGE;
        end
        
        % Summary
        function Summary(self)
            fprintf("%u - ", self.code);
			if self.loc ~= ""
                fprintf("%s ", self.loc);
            end
			if self.msg ~= ""
				fprintf("%s ", self.msg);
            end
			fprintf("\n");
        end
    end
end