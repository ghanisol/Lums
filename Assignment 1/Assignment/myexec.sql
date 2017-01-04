
rem PORJECT 2
rem CS 340

SET 	SERVEROUTPUT ON 
rem SET 	Linesize 700
rem SET 	Pagesize 60
ALTER SESSION SET nls_date_format = 'dd-mon-yy';
----------------------------------------------
----------------CREATE TABLE------------------
----------------------------------------------
EXEC DBMS_OUTPUT.PUT_LINE('#####CREATING TABLES#####');
@createtable;
----------------------------------------------
----------------POPULATE----------------------
----------------------------------------------
EXEC DBMS_OUTPUT.PUT_LINE('#####POPULATING#####');

@populate;

@trg;
@fun;
@pro;



----------------------------------------------
---EXECUTE TRIGGER, FUNCTION and PROCEDURE----
----------------------------------------------

----------------------------------------------
--------------fun_issue_book------------------
----------------------------------------------


EXEC DBMS_OUTPUT.PUT_LINE('#####ISSUING BOOKS#####');
Declare
ret_val NUMBER;
Begin
ret_val:=fun_issue_book(1,1,To_Date('3/3/2016', 'dd/mm/yyyy'));
ret_val:=fun_issue_book(2,1,To_Date('3/3/2016', 'dd/mm/yyyy'));
ret_val:=fun_issue_book(3,1,To_Date('3/3/2016', 'dd/mm/yyyy'));
ret_val:=fun_issue_book(1,7,To_Date('3/3/2016', 'dd/mm/yyyy'));
ret_val:=fun_issue_book(4,8,To_Date('3/3/2016', 'dd/mm/yyyy'));
ret_val:=fun_issue_book(4,2,To_Date('3/4/2016', 'dd/mm/yyyy'));
ret_val:=fun_issue_book(4,3,To_Date('3/4/2016', 'dd/mm/yyyy'));

End;
.
/
show error;

select * from issue;
select * from pending_request;



----------------------------------------------
----------Returning Books---------------------
----------------------------------------------
EXEC DBMS_OUTPUT.PUT_LINE('#####RETURNING BOOKS 1 2 4 21 22 23 24#####');
Declare
ret_val NUMBER;

Begin
ret_val:=fun_return_book(1,To_Date('4/4/2016', 'dd/mm/yyyy'));
ret_val:=fun_return_book(7,To_Date('4/4/2016', 'dd/mm/yyyy'));
ret_val:=fun_return_book(8,To_Date('4/4/2016', 'dd/mm/yyyy'));
ret_val:=fun_return_book(2,To_Date('4/4/2016', 'dd/mm/yyyy'));
ret_val:=fun_return_book(3,To_Date('4/4/2016', 'dd/mm/yyyy'));

End;
.
/

select * from issue;
select * from pending_request;

----------------------------------------------
----------Returning Remaining Books---------------------
----------------------------------------------

Declare
ret_val NUMBER;

Begin
ret_val:=fun_return_book(1,To_Date('4/4/2016', 'dd/mm/yyyy'));
ret_val:=fun_return_book(1,To_Date('4/4/2016', 'dd/mm/yyyy'));

End;
.
/

delete issue;
delete pending_request;

----------------------------------------------
--------------fun_issue_anyedition------------
----------------------------------------------
ALTER SESSION SET nls_date_format = 'DD/MM/YYYY';

EXEC DBMS_OUTPUT.PUT_LINE('#####ISSUING BOOKS OF ANY EDITIONS#####');
Declare
ret_val NUMBER;
Begin
ret_val:=fun_issue_anyedition(2,'DATA MANAGEMENT','C.J.DATES',To_Date('3/4/2016', 'dd/mm/yyyy'));
ret_val:=fun_issue_anyedition(4,'CALCULUS III','H.ANTON',To_Date('3/4/2016', 'dd/mm/yyyy'));
ret_val:=fun_issue_anyedition(10,'IEEE MULTIMEDIA','IEEE',To_Date('27/2/2016', 'dd/mm/yyyy'));
ret_val:=fun_issue_anyedition(2,'MIS MANAGEMENT','C.J.DATES',To_Date('3/4/2016', 'dd/mm/yyyy'));
ret_val:=fun_issue_anyedition(4,'CALCULUS III','H.ANTON',To_Date('3/4/2016', 'dd/mm/yyyy'));
ret_val:=fun_issue_anyedition(11,'ORACLE','ORACLE PRESS',To_Date('3/3/2016', 'dd/mm/yyyy'));
End;
.
/
show error;

select * from issue;
select * from pending_request;

--------------------------------------------------------------------------------------------------------------------------------------------------
-----------------------------------------------
----------print_borrower-----------------------
-----------------------------------------------
EXEC DBMS_OUTPUT.PUT_LINE('#####PRINTING BORROWER TILL 02/28/16 ONLY #####');
EXEC pro_print_borrower(To_Date('13/8/2016', 'dd/mm/yyyy'));
EXEC DBMS_OUTPUT.PUT_LINE('#####PRINTING BORROWER TILL 12/04/16 ONLY #####');
EXEC pro_print_borrower(To_Date('13/8/2016', 'dd/mm/yyyy'));

----------------------------------------------
----------print_file--------------------------
----------------------------------------------
EXEC DBMS_OUTPUT.PUT_LINE('#####PRINTING FINES TILL 16/05/16#####');
EXEC pro_print_fine(To_Date('27/12/2016', 'dd/mm/yyyy'));


---------------------------------------------
------------Displaying for user 10-----------
---------------------------------------------
EXEC DBMS_OUTPUT.PUT_LINE('#####DISPLAYING BOOKS ISSUED by USER 10 for 2/3 and 3/3#####');
EXEC pro_listborr_mon(2,4,2016);
EXEC pro_listborr_mon(11,3,2016);

---------------------------------------------
------------Printing borrower's list---------
---------------------------------------------
EXEC DBMS_OUTPUT.PUT_LINE('#####DISPLAYING BORROWER LIST#####');
EXEC pro_listborr;


---------------------------------------------
----------DROPPING ALL ----------------------
---------------------------------------------
EXEC DBMS_OUTPUT.PUT_LINE('#####DROPPING ALL#####');
@dropall;
