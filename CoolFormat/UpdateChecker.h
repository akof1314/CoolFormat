#pragma once

class CUpdateChecker
{
public:
	CUpdateChecker();
	~CUpdateChecker();

	bool IsHasNewVersion();

	void CheckUpdate();

	void DoThreadCheckUpdate();

private:
	int CompareVersion(const CString &strVersion1, const CString &strVersion2);
};

