# PhoneBook

A minimal phone book application built to the "Software Specifications" task sheet:
SDI document/view architecture, a list-view of name/sex/phone, Add/Edit/Delete, and
Store/Load via `CDocument::Serialize`.

## How each requirement is met

| # | Requirement | Where |
|---|---|---|
| 1 | SDI document-view architecture (MFC) | `PhoneBook.cpp` registers a `CSingleDocTemplate` binding `CPhoneBookDoc` + `CMainFrame` + `CPhoneBookView`. `CMainFrame` is a plain `CFrameWnd` (no ribbon), so it builds without extra toolbar-bitmap resources. |
| 2 | Display name, sex, phone number in list-view | `CPhoneBookView` derives from `CListView` and forces `LVS_REPORT` style in `PreCreateWindow`; three columns are added in `OnInitialUpdate`, and `RefreshList()` repopulates rows from the document. |
| 3 | Add/Delete/Edit phone book items | `CEntryDlg` (Name edit + Sex combo + Phone edit) is shown from the view's `OnEntryAdd` / `OnEntryEdit` / `OnEntryDelete` handlers (menu: **Entry** menu, or double-click a row to edit). The document owns the actual list and calls `UpdateAllViews` after each change. |
| 4 | Store/Load the phone book | `CPhoneBookDoc::Serialize()` writes/reads the entry count then delegates to each `CPhoneEntry::Serialize()` (which itself uses `DECLARE_SERIAL`/`IMPLEMENT_SERIAL`). Wired automatically to **File > Save / Save As / Open** by the SDI framework — no extra code needed for the menu commands. |

## Files

```

PhoneBook/
  PhoneBook.h / .cpp        CWinApp: registers the SDI doc template
  MainFrm.h / .cpp          SDI frame window (CFrameWnd)
  PhoneBookDoc.h / .cpp     CDocument: owns the list of entries, Serialize()
  PhoneBookView.h / .cpp    CListView: report-style grid + Add/Edit/Delete commands
  PhoneEntry.h / .cpp       CObject-derived record (name/sex/phone), Serialize()
  EntryDlg.h / .cpp         Add/Edit modal dialog
  
```


## Notes / possible extensions

- Serialization currently uses MFC's binary `CArchive` (the mechanism the spec calls
  out — `Serialize()` of `CDocument`), not plain text. Swapping to a text format via
  C++ fstream I/O (the spec's documented fallback) would only require rewriting
  `CPhoneBookDoc::Serialize`, since the view/dialog code doesn't touch file I/O at all.
