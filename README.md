# Eiffel_compiler
University assignment

Возьмём за правило затягивать изменения с опцией --rebase:
git pull --rebase

Syntax in Eiffel:
- таблички [старый синтаксис]: http://rigaux.org/language-study/syntax-across-languages-per-language/Eiffel.html
- Описание различных statement с различными вариантами их использования [старый синтаксис?]: https://www.infor.uva.es/~felix/priii/sintaxis.html
- https://www.eiffel.org/doc/eiffel/Quick_reference_to_the_Eiffel_programming_language
- Полезная статейка о классах: https://www.eiffel.org/doc/solutions/Eiffel_Classes
- PDF со старым синтаксисом, но полезной информацией: http://www.lirmm.fr/~ducour/Doc-objets/eiffel-tutorial.pdf
- [PDF] Стандарт ECMA-ST-WITHDRAWN/ECMA-367 https://www.ecma-international.org/publications/files/ECMA-ST-WITHDRAWN/ECMA-367,%201st%20edition,%20June%202005.pdf
- Русскоязычный перевод документации Eiffel по технологии безопасности void safety http://www.opennet.ru/base/dev/eiffel_vaid_safety.txt.html


Примеры кода uzh-software-construction

This repository holds various snippets of Eiffel in order to illustrate particular concepts I explained in the UZH course Software Construction.
https://github.com/rmatil/uzh-software-construction

---

## План семантического анализа ##
[Актуальная версия](https://docs.google.com/document/d/1D-gCdS3YgGxxdEQcVWEHZuipn_IHiS1_ANfpnq0YQLo/edit?usp=sharing)

Соглашения о преобразовании регистра имен:
Классы : UPPER_CASE
Методы/Поля/переменные : lower_case

Примечание. Для реализации видится полезным:
 - Наличие у синтаксических конструкций информации об ожидаемых типах дочерних выражений (термин: *expected*, *required*). Например, `A := B;` подразумевает `A` - левостороннее (*lvalue*) выражение.
 - Наличие у типов информации о типах, выводимых из данного. Например, `ID` приводится к *lvalue* (хотя `ID` - ещё пока не тип), `INTEGER` - к `FLOAT`.
