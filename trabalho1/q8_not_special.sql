select count(*)
from( 
    select distinct (o_custkey)
    from orders
    except 
    select distinct(o_custkey) 
    from orders
    where(0 != instr(o_comment ,'special request'))
);
