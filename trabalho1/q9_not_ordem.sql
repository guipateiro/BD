select count(*)
from( 
    select distinct (c_custkey)
    from customer 
    except 
    select distinct(c_custkey) 
    from orders inner join customer on o_custkey == c_custkey 
);