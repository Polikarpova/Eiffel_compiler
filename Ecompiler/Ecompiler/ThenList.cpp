#include "ThenList.h"

bool ThenList::create(Method* mtd, struct NThenPartList* List)
{
	if(List) {
		for(struct NThenPart* i = List->first ; i != NULL ; i = i->next) {
			// add thenPart
			ThenPart* thenPart = ThenPart::create(mtd, i);

			//если вернулся NULL, значит ошибка
			if(!thenPart)
				return false;

			this->list.append(thenPart);
			if(i == List->last) break;
		}
	}

	return true;
}


ByteCode& ThenList::toByteCode(ByteCode &bc)
{
	return bc.log("/!\\ thenList code not implemented");
}