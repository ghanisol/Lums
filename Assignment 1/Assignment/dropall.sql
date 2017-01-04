drop procedure pro_print_borrower;
drop procedure pro_print_fine;
drop procedure pro_listborr_mon;
drop procedure pro_listborr;

drop function fun_issue_book;
drop function fun_issue_anyedition;
drop function fun_most_popular;
drop function fun_return_book;
drop function fun_renew_book;

drop trigger trg_maxbooks;
drop trigger trg_issue;
drop trigger trg_notissue;

drop table pending_request;
drop table issue;
drop table borrower;
drop table books;
drop table author;

