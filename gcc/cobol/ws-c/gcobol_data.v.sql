drop view if exists G;

create view G as
with recursive
	 elems ( depth, parent, isym, level, name ) as
	 (
         SELECT 1, parent, isym, level, name
         from fields where level in (1, 77)
         UNION ALL
         SELECT p.depth + 1 as depth, P.isym, C.isym, C.level, C.name
         from elems as P join fields as C
         where C.parent = P.isym and C.level not in (88, P.level)
         )
select distinct depth, parent, isym, level, name
from elems
;

-- select * from G;

drop view if exists groups;

create view groups as
with recursive
	 elems ( depth, parent, isym, level, name, occurs,
		type, capacity, digits, picture )
	 AS (
         SELECT 1,
         isym, isym, level, name,
         upper_bound - lower_bound as occurs,
	 type, capacity, digits, picture
         from fields where level in (1, 77)
         UNION ALL
         SELECT
         1 + p.depth as depth,
         P.isym, C.isym, C.level, C.name,
         C.upper_bound - C.lower_bound as occurs,
	 C.type, C.capacity, C.digits, C.picture
         from elems as P join fields as C
         where C.parent = P.isym and C.level not in (88)
         )
select distinct depth, parent, isym, level, name, occurs,
		type, capacity, digits, picture
from elems
;

drop view if exists unions;

create view unions
as
select count(*) as nU, P.isym as isym
from fields as P join fields as C
on C.parent = P.isym and C.level = P.level
group by P.isym
;

drop view if exists working_storage;

create view working_storage
as
select nU, nelem, g.* from groups as g
left join ( select count(*) as nelem, parent
	from groups where parent <> isym group by parent ) as T
on g.isym = T.parent
left join unions as U on g.isym = U.isym
order by parent, isym;

select * from working_storage;
