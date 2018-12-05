# Eiffel_compiler
University assignment

������ �� ������� ���������� ��������� � ������ --rebase:
git pull --rebase

Syntax in Eiffel:
- �������� [������ ���������]: http://rigaux.org/language-study/syntax-across-languages-per-language/Eiffel.html
- �������� ��������� statement � ���������� ���������� �� ������������� [������ ���������?]: https://www.infor.uva.es/~felix/priii/sintaxis.html
- https://www.eiffel.org/doc/eiffel/Quick_reference_to_the_Eiffel_programming_language
- �������� �������� � �������: https://www.eiffel.org/doc/solutions/Eiffel_Classes
- PDF �� ������ �����������, �� �������� �����������: http://www.lirmm.fr/~ducour/Doc-objets/eiffel-tutorial.pdf
- [PDF] �������� ECMA-ST-WITHDRAWN/ECMA-367 https://www.ecma-international.org/publications/files/ECMA-ST-WITHDRAWN/ECMA-367,%201st%20edition,%20June%202005.pdf
- ������������� ������� ������������ Eiffel �� ���������� ������������ void safety http://www.opennet.ru/base/dev/eiffel_vaid_safety.txt.html


������� ���� uzh-software-construction

This repository holds various snippets of Eiffel in order to illustrate particular concepts I explained in the UZH course Software Construction.
https://github.com/rmatil/uzh-software-construction

---

## ���� �������������� ������� ##
[���������� ������](https://docs.google.com/document/d/1D-gCdS3YgGxxdEQcVWEHZuipn_IHiS1_ANfpnq0YQLo/edit?usp=sharing)

���������� � �������������� �������� ����:
������ : UPPER_CASE
������/����/���������� : lower_case

����������. ��� ���������� ������� ��������:
 - ������� � �������������� ����������� ���������� �� ��������� ����� �������� ��������� (������: *expected*, *required*). ��������, `A := B;` ������������� `A` - ������������� (*lvalue*) ���������.
 - ������� � ����� ���������� � �����, ��������� �� �������. ��������, `ID` ���������� � *lvalue* (���� `ID` - ��� ���� �� ���), `INTEGER` - � `FLOAT`.
