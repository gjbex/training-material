classdef stats < handle

    properties(SetAccess=private)
        nr_items = 0
        items_sum = 0.0
        items_sum2 = 0.0
    end
    
    methods
    
        function s = stats()
        end
        
        function add(s, x)
            s.nr_items = s.nr_items + 1;
            s.items_sum = s.items_sum + x;
            s.items_sum2 = s.items_sum2 + x.^2;
        end
        
        function m = mean(s)
            m = s.items_sum/s.nr_items;
        end
        
        function stdev = stddev(s)
            stdev = sqrt((s.items_sum2 - s.items_sum.^2/s.nr_items)/(s.nr_items - 1));
        end
        
        function nr = n(s)
            nr = s.nr_items;
        end
        
    end

end