@echo on
echo 请检查当前路径是否正确。
pause 
for /r %%f in (*.aps *.config *.db *.db-shm *.db-wal *.FileListAbsolute.txt *.iobj *.ipdb *.ipch *.log *.obj *.opendb *.pch *.res *.sari *.sbr *.suo *.tlog *.tmp *.use) do del /s /q /f "%%f"
pause 