#include "stdafx.h"
#include "Observer.h"

int CMessager::Advise(CSinker* pSinker)
{
	size_t i = 0;

	if (pSinker == NULL) return m_sinkers.size();

	for (; i < m_sinkers.size(); i++){
		if (m_sinkers[i] == pSinker)
			break;
	}

	if (i == m_sinkers.size())
		m_sinkers.push_back(pSinker);

	return m_sinkers.size();
}

int CMessager::Unadvise(const CSinker* pSinker)
{
	size_t i = 0;

	if (pSinker == NULL) return m_sinkers.size();

	for (; i < m_sinkers.size(); i++){
		if (m_sinkers[i] == pSinker)
			break;
	}

	if (i != m_sinkers.size())
		m_sinkers.erase(m_sinkers.begin() + i);

	return m_sinkers.size();

}

void CMessager::NotifyMsg(int msgid, char* msg, int msglen)
{
	for (size_t i = 0; i < m_sinkers.size(); i++){
		m_sinkers[i]->Update(msgid, msg, msglen);
	}
}