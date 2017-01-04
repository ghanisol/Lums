rem CS 340 Programming Assignment 1
rem Muhammad Faizan Ul Ghani
rem s18100279

set serveroutput on;
exec DBMS_OUTPUT.PUT_LINE('Query #1');
select p.pat_id from patent p, categories c where p.cat = c.cat and p.subcat = c.subcat and (c.catnamelong = 'Electrical AND Electronic' or c.catnamelong = 'Chemical');
exec DBMS_OUTPUT.PUT_LINE('Query #2');
select i.lastname, i.firstname, i.country, i.postate from inventor i, patent p, categories c where p.pat_id = i.patentnum and p.cat = c.cat and p.subcat = c.subcat and (c.catnamelong = 'Electrical AND Electronic' or c.catnamelong = 'Chemical');
exec DBMS_OUTPUT.PUT_LINE('Query #3');
select p.pat_id from patent p, inventor i where p.pat_id = i.patentnum and i.country = 'US' and (i.postate = 'CA' OR i.postate = 'NJ') and i.invseq = 1;
exec DBMS_OUTPUT.PUT_LINE('Query #4');
select t.compname from (select c.compname, count(*) tot_count from company c, patent p where c.assignee = p.assignee group by c.compname) t where t.tot_count = (select max(tCount) from (select count(*) tCount from patent group by assignee));
exec DBMS_OUTPUT.PUT_LINE('Query #5');
select t.compname from (select c.compname, count(*) tot_count from company c, patent p, categories ca where c.assignee = p.assignee and ca.cat = p.cat and ca.catnamelong = 'Chemical' group by compname) t where t.tot_count = (select max(t.tot_count) from (select c.compname, count(*) tot_count from company c, patent p, categories ca where c.assignee = p.assignee and ca.cat = p.cat and ca.catnamelong = 'Chemical' group by compname) t);
exec DBMS_OUTPUT.PUT_LINE('Query #6');
select c.compname from company c, patent p where c.assignee = p.assignee group by c.compname having count(*) > 2;
exec DBMS_OUTPUT.PUT_LINE('Query #7');
select t.cat, max(tot_count) max_tot_count from (select p.assignee, ca.cat, count(*) tot_count from categories ca, patent p where p.cat = ca.cat group by p.assignee, ca.cat) t group by t.cat) t1 where p.cat = t1.cat gro; 
exec DBMS_OUTPUT.PUT_LINE('Query #8');
select t.firstname, t.lastname, t.tot_count from (select i.firstname, i.lastname, count(*) tot_count from inventor i, patent p where p.pat_id = i.patentnum group by i.firstname, i.lastname) t where t.tot_count = (select max(t.tot_count) from (select i.firstname, i.lastname, count(*) tot_count from inventor i, patent p where p.pat_id = i.patentnum group by i.firstname, i.lastname) t);
exec DBMS_OUTPUT.PUT_LINE('Query #10');
select t.cited from (select c.cited, count(*) tot_count from citations c group by cited) t where t.tot_count = (select max(t.tot_count) from (select c.cited, count(*) tot_count from citations c group by cited) t);
exec DBMS_OUTPUT.PUT_LINE('Query #11');
select t.citing from (select c.citing, count(*) tot_count from citations c group by citing) t where t.tot_count = (select max(t.tot_count) from (select c.citing, count(*) tot_count from citations c group by citing) t);
exec DBMS_OUTPUT.PUT_LINE('Query #12');
select i.firstname, i.lastname, i.invseq, i.city, i.postate from inventor i where i.patentnum = (select t.cited from (select c.cited, count(*) tot_count from citations c group by cited) t where t.tot_count = (select max(t.tot_count) from (select c.cited, count(*) tot_count from citations c group by cited) t));
exec DBMS_OUTPUT.PUT_LINE('Query #13');
select t.firstname, t.lastname, t.city, t.postate from (select i.firstname, i.lastname, i.city, i.postate, count(*) tot_count from inventor i, patent p where p.pat_id = i.patentnum group by i.firstname, i.lastname, i.city, i.postate) t where t.tot_count = (select max(t.tot_count) from (select i.firstname, i.lastname, count(*) tot_count from inventor i, patent p where p.pat_id = i.patentnum group by i.firstname, i.lastname) t);
exec DBMS_OUTPUT.PUT_LINE('Query #14');
select p.pat_id from patent p where not exists (select * from citations c where c.cited = p.pat_id);
exec DBMS_OUTPUT.PUT_LINE('Query #15');
select i.firstname, i.lastname, i.city, i.postate from inventor i where i.patentnum in (select p.pat_id from patent p where not exists (select * from citations c where c.cited = p.pat_id));
exec DBMS_OUTPUT.PUT_LINE('Query #16');
select p.pat_id, ca.cat, ca.subcat, c.compname from (select c.cited, count(*) tot_count from citations c group by cited having count(*) > 2) t, company c, categories ca, patent p where p.pat_id = t.cited and p.cat = ca.cat and p.subcat = ca.subcat and c.assignee = p.assignee;
exec DBMS_OUTPUT.PUT_LINE('Query #17');
select c.cat, c.subcat, count(*) tot_count from patent p, categories c where p.cat = c.cat and p.subcat = c.subcat group by c.cat, c.subcat;
exec DBMS_OUTPUT.PUT_LINE('Query #18');
select avg(t.tot_count) from (select p.assignee, count(*) tot_count from inventor i, patent p where i.invseq = 1 and i.postate = 'CA' and i.patentnum = p.pat_id group by p.assignee) t;
exec DBMS_OUTPUT.PUT_LINE('Query #19');
select avg(t_nj.tot_count_nj) - avg(t_ca.tot_count_ca) from (select p.assignee, count(*) tot_count_ca from inventor i, patent p where i.invseq = 1 and i.postate = 'CA' and i.patentnum = p.pat_id group by p.assignee) t_ca, (select p.assignee, count(*) tot_count_nj from inventor i, patent p where i.invseq = 1 and i.postate = 'NJ' and i.patentnum = p.pat_id group by p.assignee) t_nj;
exec DBMS_OUTPUT.PUT_LINE('Query #20');
select c.compname from company c, patent p where c.assignee = p.assignee group by c.compname having count(*) > (select avg(t.tot_count) from (select p.assignee, count(*) tot_count from inventor i, patent p where i.invseq = 1 and i.postate = 'NJ' and i.patentnum = p.pat_id group by p.assignee) t);
exec DBMS_OUTPUT.PUT_LINE('Query #21');
select avg(t.tot_count) from (select p.pat_id, count(*) tot_count from inventor i, patent p, categories c where i.patentnum = p.pat_id and p.cat = c.cat and p.subcat = c.subcat and c.catnamelong= 'Chemical' group by p.pat_id) t;
exec DBMS_OUTPUT.PUT_LINE('Query #22');
select p.pat_id from categories c, patent p, inventor i where i.patentnum = p.pat_id and c.cat = p.cat and c.subcat = p.subcat and c.catnamelong = 'Chemical' group by p.pat_id having count(*) < (select avg(t.tot_count) from (select p.pat_id, count(*) tot_count from inventor i, patent p, categories c where i.patentnum = p.pat_id and p.cat = c.cat and p.subcat = c.subcat and c.catnamelong= 'Chemical' group by p.pat_id) t);
exec DBMS_OUTPUT.PUT_LINE('Query #23');
select t.f_name, t.l_name from (select i1.firstname f_name, i1.lastname l_name from inventor i1, inventor i2, citations c1 where i1.patentnum = c1.cited and i2.patentnum = c1.citing and i1.firstname = i2.firstname and i2.lastname = i1.lastname) t;
exec DBMS_OUTPUT.PUT_LINE('View A');
create view VIEWA as select p.pat_id, i.firstname, i.lastname, p.gyear, c.compname, ca.catnamelong, ca.catnameshort from categories ca, company c, patent p, inventor i where ca.cat = p.cat and ca.subcat = p.subcat and p.pat_id = i.patentnum and p.assignee = c.assignee and i.invseq = 1;  
exec DBMS_OUTPUT.PUT_LINE('View B');
create view VIEWB as select distinct * from (select c.assignee, c.compname, ca.catnamelong, ca.catnameshort, t.tot_count from categories ca, company c, patent p, (select count(*) tot_count, c.compname from company c, patent p where c.assignee = p.assignee group by c.compname) t where ca.cat = p.cat and ca.subcat = p.subcat and c.assignee = p.assignee and t.compname = c.compname);

	
