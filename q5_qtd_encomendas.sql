select N.n_name,count(O.o_orderkey) 
from (nation N inner join customer C on N.n_nationkey == C.c_nationkey) inner join orders O on O.o_custkey == C.c_custkey 
group by N.n_name 
order by count(O.o_orderkey) DESC;