<?php
	// Создаем новый класс Coor:
	class Coor {
		// данные (свойства):
		var $name;

		// методы:
		function Getname() {
			echo "<h3>John</h3>";
		}

	}

	// Создаем объект класса Coor:
	$object = new Coor;
	// Получаем доступ к членам класса:
	$object->name = 'Alex\nfrfrrf
	ijr\'gi';
	echo $object->name;
	// Выводит 'Alex'
	// А теперь получим доступ к методу класса (фактически, к функции внутри класса):
	$object->Getname();
	// Выводит 'John' заглавными буквами
