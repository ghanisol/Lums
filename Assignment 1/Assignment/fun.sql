create or replace function fun_issue_book (br_id number, b_id number, cur_date date) return number as
	bstat books.status%type;

	begin
		select b.status into bstat from books b where b.book_id = b_id;

		if bstat != 'issued' then
			insert into issue values(b_id, br_id, cur_date, NULL);
			return 1;
		else
			insert into pending_request values(b_id, br_id, cur_date, NULL);
			return 0;
		end if;	

	end fun_issue_book;

.
run;

create or replace function fun_issue_anyedition (br_id number, b_title varchar2, a_name varchar2, cur_date date) return number as
	b_id books.book_id%type;

	begin

		begin
			select t.book_id into b_id from (select b.book_id from books b, author a where b.book_title = b_title and a.name = a_name and NOT(b.status = 'issued') order by b.edition desc) t where rownum = 1; 
		
		exception
			when NO_DATA_FOUND then
				b_id := -10;
		end; 

		if b_id != -10 then
			insert into issue values(b_id, br_id, cur_date, NULL);
			return 1;
		else
			select t.book_id into b_id from (select i.book_id from books b, issue i where b.book_title = b_title and i.book_id = b.book_id and i.return_date is NULL order by i.issue_date asc) t where rownum = 1;
			insert into pending_request values(b_id, br_id, cur_date, NULL);
			return 0;

		end if;

	end fun_issue_anyedition;
.
run;

create or replace function fun_most_popular (month number, year number) return number as
	b_id books.book_id%type;

	begin
		for val in 
		(select t.book_id from (select b.book_id, count(b.book_id) tot_count from books b, issue i where b.book_id = i.book_id and to_char(i.issue_date, 'mm') = month and to_char(i.issue_date, 'yyyy') = year group by b.book_id) t where t.tot_count = (select max(t.tot_count) from (select b.book_id, count(b.book_id) tot_count from books b, issue i where b.book_id = i.book_id and to_char(i.issue_date, 'mm') = month and to_char(i.issue_date, 'yyyy') = year group by b.book_id) t))
	
		loop
			dbms_output.put_line(val.book_id);
		end loop;
		return 1;
	end;

.
run;

create or replace function fun_return_book (b_id number, cur_date date) return number as

	br_id number;

	begin
		update issue i set i.return_date = cur_date where i.book_id = b_id and i.return_date is NULL;

		begin
			select t.requester_id into br_id from (select pr.requester_id from pending_request pr where pr.book_id = b_id and pr.issue_date is NULL order by pr.request_date) t where rownum = 1;
		exception
			when NO_DATA_FOUND then
				br_id := -1;
		end;

		if br_id != -1 then
			update pending_request pr set pr.issue_date = cur_date where pr.requester_id = br_id and pr.book_id = b_id and pr.issue_date is NULL;
			insert into issue values(b_id, br_id, cur_date, NULL);
			return 1;
		else
			return 0;
		end if;

	end;

.
run;

create or replace function fun_renew_book (br_id number, b_id number, cur_date date) return number as

	isPen number := 1;
	isIssued number := 1;
	temp_b_id number;

	begin
		begin
			select i.book_id into temp_b_id from issue i where i.book_id = b_id and i.borrower_id = br_id;
		exception
			when NO_DATA_FOUND then
				isIssued := 0;
		end;

		begin
			select pr.book_id into temp_b_id from pending_request pr where pr.book_id = b_id;
		exception
			when NO_DATA_FOUND then
				isPen := 0;
		end;

		if isPen = 0 and isIssued = 1 then
			update issue i set i.issue_date = cur_date where i.book_id = b_id and i.borrower_id = br_id;
			return 1;
		else
			return 0;
		end if;

	end;

.
run;