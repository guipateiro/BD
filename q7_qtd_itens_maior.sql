select N.n_name,sum(L.l_quantity) 
from ((nation N inner join customer C on N.n_nationkey == C.c_nationkey) inner join orders O on O.o_custkey == C.c_custkey) inner join lineitem L on O.o_orderkey == L.l_orderkey 
group by N.n_name
having (sum(L.l_quantity) > 62000)
order by sum(L.l_quantity) DESC;
