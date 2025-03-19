PROG = ..tests/Listing-17-3/Listing-17-3.cbl

report: db
	sqlite3 -column -header -init gcobol_data.v.sql db \
		"select * from groups order by isym"

renew:	csv
	@rm -f -v db
	sqlite3 db < gcobol_data.t.sql
	sqlite3 db < gcobol_data.v.sql
	sqlite3 -csv db ".import './csv' fields"

db: 	csv
	sqlite3 db < gcobol_data.ddl

csv:
	GCOBOL_DATA=$@ gcobol -oo $(PROG)
