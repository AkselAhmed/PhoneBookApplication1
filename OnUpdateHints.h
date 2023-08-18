#pragma once

/////////////////////////////////////////////////////////////////////////////
// OnUpdateHints

///<summary> Енумератор подсказка при OnUpdate</summary>
enum OnUpdateHints
{
	///<summary> При редакция на елемент</summary>
	OnUpdateHintUpdate = 1,
	///<summary> При вмъкване на елемент</summary>
	OnUpdateHintInsert = 2,
	///<summary> При изтриване на елемент</summary>
	OnUpdateHintDelete = 3
};