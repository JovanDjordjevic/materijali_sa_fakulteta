drop database if exists vezbe;
create database vezbe character set = utf8;
use vezbe;

-- **XPath primeri (osnovno)**
-- Funkcijom 'ExtractValue(content, query)' mozemo da vrsimo XPath upit nad xml sadrzajem

set @xml_osnovni = '<a><b>X</b><b>Y</b></a>';
-- <a>
--    <b>X</b>
--    <b>Y<b/>
-- </a>

set @xml_tekst_pod_a = '<a>tekst<b>X</b><b>Y</b></a>';
-- <a>
--    tekst
--    <b>X</b>
--    <b>Y</>
-- </a>

set @xml_attr = '<a><b name="1">X</b><b name="2">Y</b></a>';
-- <a>
--    <b name="1">X</b>
--    <b name="2">Y</>
-- </a>

set @xml_abcd = '<a><b><c>1</c><c>2</c></b><b><c>3</c><c>4<d>5</d></c></b></a>';
-- <a>
--    <b>
--       <c>1</c>
--       <c>2</c>
--    </b>
--    <b>
--       <c>3</c>
--       <c>
--          4
--          <d>5</d>
--       </c>
--    </b>
-- </a>

set @xml_abcb = '<root><a><b>1</b></a><c><b>2</b></c></root>';
-- <root>
--   <a>
--      <b>1</b>
--   </a>
--   <c>
--      <b>2</b>
--   </c>
-- </root>

select ExtractValue(@xml_osnovni, 'a');
-- Ocekivani izlaz: "", jer 'a' ima samo podelemente, a tekst je prazan
-- *'/a' i 'a' je isto

select ExtractValue(@xml_tekst_pod_a, 'a');
-- Ocekivani izlaz: "tekst"

-- '//x' dohvata sve cvorove x, gde god oni bili u hijearhiji
select ExtractValue(@xml_osnovni, '//b');
-- Ocekivani izlaz: "X Y", jer biramo sadrzaj (tekst) svih `b`-ova

select ExtractValue(@xml_abcd, '//b');
-- Ocekivani izlaz: "", jer b nema tekst

-- '*' dohvata svu direktnu decu
select ExtractValue(@xml_abcd, '//b/*');
-- Ocekivani izlaz: "1 2 3 4", jer smo izabrali sav sadrzaj dece `b`-a, ali
-- nema 5, jer je to nije direktno dete od `b`

-- '[i]' je prvo pojavljivanje elementa 'b' u hijearhiji
select ExtractValue(@xml_osnovni, '//b[1]');
-- Ocekivani izlaz: "X", jer biramo prvo `b`

select ExtractValue(@xml_osnovni, '//b[2]');
-- Ocekivani izlaz: "Y", jer biramo drugo `b`

select ExtractValue(@xml_attr, '//b[@name=1]');
-- Ocekivani izlaz: "X", dohvata samo one 'b'-ove koji imaju vrednost atributa 'name="1"'

select ExtractValue(@xml_attr, '//b[@name]');
-- Ocekivani izlaz: "X Y", dohvata samo one 'b'-ove koji imaju atribut 'name'

select ExtractValue(@xml_tekst_pod_a, '//b/..');
-- Ocekivani izlaz: "tekst", dohvata za svaki 'b' tekst roditelja

-- 'count(...)' prebrojava broj pojavljivanja
select ExtractValue(@xml_osnovni, 'count(//b)');
-- Ocekivani izlaz: "2"

select ExtractValue(@xml_abcb, '//a/b');
-- Ocekivani izlaz: "1", jer dohvata samo sadrzaj 'b'-ova koji su pod nekim 'a'

select ExtractValue(@xml_abcb, 'root/c/b');
-- Ocekivani izlaz: "2"

-- Funkcijom UpdateXML(content, query, value) mozemo da azuriramo xml sadrzaj `content`
-- tako sto rezultate upita `query` zamenimo `value`

select UpdateXML(@xml_osnovni, '/a', '<z>abc</z>');
-- Ocekivani izlaz: "<z>abc</z>", jer smo zamenili sve korene elemente 'a' sa '<z>abc</z>'

select UpdateXML(@xml_osnovni, '/b', '<z>abc</z>');
-- Ocekivani izlaz: "<a><b>X</b><b>Y</b></a>", je nema korenih 'b'-ova

select UpdateXML(@xml_osnovni, '//b[1]', '<z>abc</z>');
-- Ocekivani izlaz: "<a><z>abc</z><b>Y</b></a>"

select UpdateXML(@xml_osnovni, '//b', '<z>abc</z>');
-- Ocekivani izlaz: "<a><b>X</b><b>Y</b></a>" (id), jer ima vise b-ova pod 'a'

select UpdateXML(@xml_abcd, '//d', '<z>abc</z>');
-- Ocekivani izlaz: "<a><b><c>1</c><c>2</c></b><b><c>3</c><c>4<d>5</d></c></b></a>"

-- Dodatak:
-- https://www.w3schools.com/xml/xpath_syntax.asp