#pragma once

// Token from WLib\Sys\Api\Win32\Kernel\Thread\CrSect.h

class CComAutoCriticalSection
{
  CRITICAL_SECTION crSect;

public:
  inline CComAutoCriticalSection()
  {
    memset(&crSect, 0, sizeof(CRITICAL_SECTION));
    InitializeCriticalSection(&crSect);
  }
 
  inline ~CComAutoCriticalSection()
  {
    DeleteCriticalSection(&crSect);
  }
 
  inline bool Lock()
  {
    EnterCriticalSection(&crSect);
    return true;
  }
 
  inline bool TryLock()
  {
    return TryEnterCriticalSection(&crSect);
  }
 
  inline void Unlock()
  {
    LeaveCriticalSection(&crSect);
  }
};
