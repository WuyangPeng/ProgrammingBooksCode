@echo on
echo ���鵱ǰ·���Ƿ���ȷ��
pause 
for /r %%f in (*.aps *.config *.db *.db-shm *.db-wal *.FileListAbsolute.txt *.iobj *.ipdb *.ipch *.log *.obj *.opendb *.pch *.res *.sari *.sbr *.suo *.tlog *.tmp *.use) do del /s /q /f "%%f"
pause 