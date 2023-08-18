#pragma once

/////////////////////////////////////////////////////////////////////////////
// TransactionExits

///<summary> Енумератор за транзакцията</summary>
enum TransactionExits
{
	///<summary> Изпълняване на транзакцията</summary>
	TransactionExitCommit = 0,
	///<summary> Абортиране на транзакцията</summary>
	TransactionExitAbort = 1
};