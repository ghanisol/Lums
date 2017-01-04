create or replace procedure pro_print_borrower (cur_date date) as
	br_name borrower.name%type;
	b_title books.book_title%type;
	i_date issue.issue_date%type;
	days number;
	l_5 number;
	l_10 number;
	l_15 number;
	g_15 number;

	cursor cur is
		select br.name, b.book_title, i.issue_date from books b, borrower br, issue i where b.book_id = i.book_id and i.borrower_id = br.borrower_id for update;

	begin
		open cur;

		dbms_output.put_line('Borrower Name'|| chr(9) || 'Book Name' || chr(9) || '<= 5 days' || chr(9) || '<= 10 days' || chr(9) || '<= 15 days' || chr(9) || '> 15 days');
		loop
			fetch cur into br_name, b_title, i_date;

			exit when cur%NOTFOUND;

			days := cur_date - i_date;

			if days <= 5 then
				l_5 := days;
			elsif days <= 10 then
				l_10 := days;
			elsif days <= 15 then
				l_15 := days;
			else
				g_15 := days;
			end if;

			dbms_output.put_line(br_name || chr(9) || b_title || chr(9) || l_5 || chr(9) || l_10 || chr(9) || l_15 || chr(9) || g_15);

			l_5 := NULL;
			l_10 := NULL;
			l_15 := NULL;
			g_15 := NULL;


		end loop;
		close cur;
	end;

.
run;

create or replace procedure pro_print_fine (cur_date date) as
	br_name borrower.name%type;
	b_id books.book_id%type;
	i_date issue.issue_date%type;
	days number;
	fine number;

	cursor cur is
		select br.name, i.book_id, i.issue_date from borrower br, issue i where br.borrower_id = i.borrower_id and i.return_date is NULL for update;

	begin
		open cur;

		dbms_output.put_line('Borrower Name'|| chr(9) || 'Book ID' || chr(9) || 'FINE / $');
		loop
			fetch cur into br_name, b_id, i_date;

			exit when cur%NOTFOUND;

			days := cur_date - i_date;

			days := days - 5;

			if days > 0 then
				fine := days * 5;
			else
				fine := 0;
			end if; 

			dbms_output.put_line(br_name || chr(9) || b_id || chr(9) || fine);

		end loop;
		close cur;
	end;

.
run;

create or replace procedure pro_listborr_mon (br_id number, month number, year number) as
	br_name borrower.name%type;
	b_id books.book_id%type;
	b_title books.book_title%type;
	i_date issue.issue_date%type;
	r_date issue.return_date%type;

	cursor cur is
		select br.name, b.book_id, b.book_title, i.issue_date, i.return_date from borrower br, books b, issue i where br.borrower_id = br_id and br.borrower_id = i.borrower_id and b.book_id = i.book_id and to_char(i.issue_date, 'mm') = month and to_char(i.issue_date, 'yyyy') = year for update;

	begin
		open cur;

		dbms_output.put_line('Borrower ID' || chr(9) || 'Borrower Name'|| chr(9) || 'Book ID' || chr(9) || 'Book Title'|| chr(9) || 'ISSUE DATE' || chr(9) || 'RETURN DATE');
		loop
			fetch cur into br_name, b_id, b_title, i_date, r_date;

			exit when cur%NOTFOUND; 

			dbms_output.put_line(br_id || chr(9) || br_name || chr(9) || b_id|| chr(9) || b_title|| chr(9) || i_date|| chr(9) || r_date);

		end loop;
		close cur;
	end;

.
run;

create or replace procedure pro_listborr as 
	br_name borrower.name%type;
	b_id books.book_id%type;
	i_date issue.issue_date%type;

	cursor cur is
		select br.name, b.book_id, i.issue_date from borrower br, books b, issue i where br.borrower_id = i.borrower_id and b.book_id = i.book_id and i.return_date is NULL;

	begin
		open cur;

		dbms_output.put_line('Borrower Name' || chr(9) || 'Book ID' || chr(9) || 'Issue Date');
		loop
			fetch cur into br_name, b_id, i_date;

			exit when cur%NOTFOUND;

			dbms_output.put_line(br_name || chr(9) || b_id || chr(9) || i_date);

		end loop;
		close cur;
	end;

.
run; 