;;  Russian language strings for the Windows Ekiga NSIS installer.
;;  Windows Code page: 1251
;;  Author: Alexey Loukianov a.k.a. LeXa2
;;
;;  Note: To translate this file:
;;  - download this file on your computer
;;  - translate all the strings into your language
;;  - put the appropriate Windows Code Page (the one you use) above
;;  - add yourself as Author above
;;  - send us the file and remind us:
;;    - to add the entry for your file in ekiga.nsi
;;      (MUI_LANGUAGE and EKIGA_MACRO_INCLUDE_LANGFILE)
;;    - to replace everywhere in your file
;;      "!insertmacro EKIGA_MACRO_DEFAULT_STRING" with "!define"

; License Page
!define EKIGA_LICENSE_BUTTON			"����� >"
!define EKIGA_LICENSE_BOTTOM_TEXT			"$(^Name) ����������� �� ����� �������������� GNU General Public License (GPL). �������������� ��� ����� �������� ���������� ������ ��� �������. $_CLICK"

; Components Page
!define EKIGA_SECTION_TITLE			"������������ Ekiga (�����������)"
!define EKIGA_SHORTCUTS_SECTION_TITLE		"������"
!define EKIGA_DESKTOP_SHORTCUT_SECTION_TITLE	"������� ����"
!define EKIGA_STARTMENU_SHORTCUT_SECTION_TITLE	"���� ����"
!define EKIGA_SECTION_DESCRIPTION			"�������� ���������� � ����� Ekiga"
!define EKIGA_STARTUP_SECTION_DESCRIPTION	"���������� Ekiga ��� ������ Windows"
!define EKIGA_SHORTCUTS_SECTION_DESCRIPTION	"������ ��� ������� Ekiga"
!define EKIGA_DESKTOP_SHORTCUT_DESC		"������� ����� ��� Ekiga �� ������� �����"
!define EKIGA_STARTMENU_SHORTCUT_DESC		"������� ��� Ekiga ����� � ���� ����"

; Ekiga Section Prompts and Texts
!define EKIGA_UNINSTALL_DESC			"Ekiga (������ ��������)"
!define EKIGA_RUN_AT_STARTUP			"��������� Ekiga ��� ������ Windows"
!define EKIGA_PROMPT_CONTINUE_WITHOUT_UNINSTALL	"������ �������� ��� ������������� ������ Ekiga. ��������� ����� ������ ����� ���������� ��� �������� ������������ ������."

; Uninstall Section Prompts
!define un.EKIGA_UNINSTALL_ERROR_1		"��������� �������� �� ������ ����� ������ ������� ��� Ekiga.$\r��������� ����� ������������ Ekiga ��� ���������� �� ��� ������� ������ ������� ������������."
!define un.EKIGA_UNINSTALL_ERROR_2		"� ��� ����������� ����������� ���������� ��� �������� ����� ����������."
