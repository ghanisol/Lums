create or replace trigger trg_maxbooks
	before insert on issue
	for each row

	declare
		bid issue.borrower_id%type;
		bstat borrower.status%type;
		bcnt number := 0;

	begin

		begin
			select i.borrower_id, b.status, count(b.borrower_id)
			into bid, bstat, bcnt from borrower b, issue i
			where b.borrower_id = i.borrower_id and :new.borrower_id = b.borrower_id
			group by i.borrower_id, b.status;
		exception
			when NO_DATA_FOUND then
				bid := NULL;
				bstat := NULL;
		end;


		if bstat = 'faculty' then 
		    if bcnt >= 3 then
		    	RAISE_APPLICATION_ERROR(-20000, 'A faculty can not issue more than 3 books');
		    end if;
		else 
			if bcnt >= 2 then
				RAISE_APPLICATION_ERROR(-20000, 'A student can not issue more than 2 books');
			end if;
		end if;

	end;
.
run;

create or replace trigger trg_issue
	after insert on issue
	for each row

	begin
		update books b set b.status = 'issued' where b.book_id = :new.book_id;
	end;

.
run;	

create or replace trigger trg_notissue
	after update of return_date on issue
	for each row

	begin
		update books b set b.status = 'not_issued' where b.book_id = :new.book_id;
	end;

.
run;