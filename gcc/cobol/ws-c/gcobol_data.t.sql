create table fields (
    isym        integer not NULL,
    parent      integer not NULL,
    level       integer not NULL,
    name        text    not NULL,
    offset      integer not NULL,
    type        text    not NULL,
    attr        text    not NULL,
    -- occurs
    odo         integer not NULL,
    lower_bound integer not NULL,
    upper_bound integer not NULL,
    line        integer not NULL,
    -- data
    memsize     integer not NULL,
    capacity    integer not NULL,
    digits      integer not NULL,
    rdigits     integer not NULL,
    picture     text        NULL
);

create view groups as
select	P.isym, P.parent,
	P.level, P.name, p.type as 'parent_type',
	P.upper_bound - P.lower_bound as occurs,
	C.name as 'member', C.type,
	C.capacity, C.digits, C.picture
from (
	select * from fields
        where level not in (0, 88)
        and parent not in (select isym from fields)
        ) as P
        left join fields as C
on    P.isym = C.parent
and   C.level <> 88
;
