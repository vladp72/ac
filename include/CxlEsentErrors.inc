//**********************************************************************
//*********************** JET ERROR CODES ******************************
//**********************************************************************
// define following macro, and include this file
//
// ESENT_SUCCESS_ENTRY(symbol, code, string)   - error codes.          Starts with ESENT_err##symbol
// ESENT_ERR_ENTRY(symbol, code, string)       - error codes.          Starts with ESENT_err##symbol
// ESENT_WRN_ENTRY(symbol, code, string)       - warning codes.        Starts with ESENT_wrn##symbol
// ESENT_WRN_ENTRY_SHORT(symbol, code, string) - warning codes.        Starts with wrn##symbol
// ESENT_ALIASE_ERR_ENTRY(symbol1, symbol2)    - alias for an error.   ESENT_err##symbol1 is defined as ESENT_err##symbol2
// ESENT_ALIASE_WRN_ENTRY(symbol1, symbol2)    - alias for a waarning. ESENT_wrn##symbol1 is defined as ESENT_wrn##symbol2
//
//
//
ESENT_SUCCESS_ENTRY(Success, 0, "Successful Operation")
//
//
//
ESENT_WRN_ENTRY(Nyi, -1, "Function Not Yet Implemented")
ESENT_ERR_ENTRY(RfsFailure, -100, "Resource Failure Simulator failure")
ESENT_ERR_ENTRY(RfsNotArmed, -101, "Resource Failure Simulator not initialized")
ESENT_ERR_ENTRY(FileClose, -102, "Could not close file")
ESENT_ERR_ENTRY(OutOfThreads, -103, "Could not start thread")
ESENT_ERR_ENTRY(TooManyIO, -105, "System busy due to too many IOs")
ESENT_ERR_ENTRY(TaskDropped, -106, "A requested async task could not be executed")
ESENT_ERR_ENTRY(InternalError, -107, "Fatal internal error")
ESENT_ERR_ENTRY(DisabledFunctionality, -112, "You are running MinESE, that does not have all features compiled in.This functionality is only supported in a full version of ESE.")
ESENT_ERR_ENTRY(UnloadableOSFunctionality, -113, "The desired OS functionality could not be located and loaded / linked.")
ESENT_ERR_ENTRY(DatabaseBufferDependenciesCorrupted, -255, "Buffer dependencies improperly set. Recovery failure")
ESENT_WRN_ENTRY(RemainingVersions, 321, "The version store is still active")
ESENT_ERR_ENTRY(PreviousVersion, -322, "Version already existed. Recovery failure")
ESENT_ERR_ENTRY(PageBoundary, -323, "Reached Page Boundary")
ESENT_ERR_ENTRY(KeyBoundary, -324, "Reached Key Boundary")
ESENT_ERR_ENTRY(BadPageLink, -327, "Database corrupted")
ESENT_ERR_ENTRY(BadBookmark, -328, "Bookmark has no corresponding address in database")
ESENT_ERR_ENTRY(NTSystemCallFailed, -334, "A call to the operating system failed")
ESENT_ERR_ENTRY(BadParentPageLink, -338, "Database corrupted")
ESENT_ERR_ENTRY(SPAvailExtCacheOutOfSync, -340, "AvailExt cache doesn't match btree")
ESENT_ERR_ENTRY(SPAvailExtCorrupted, -341, "AvailExt space tree is corrupt")
ESENT_ERR_ENTRY(SPAvailExtCacheOutOfMemory, -342, "Out of memory allocating an AvailExt cache node")
ESENT_ERR_ENTRY(SPOwnExtCorrupted, -343, "OwnExt space tree is corrupt")
ESENT_ERR_ENTRY(DbTimeCorrupted, -344, "Dbtime on current page is greater than global database dbtime")
ESENT_WRN_ENTRY(UniqueKey, 345, "seek on non-unique index yielded a unique key")
ESENT_ERR_ENTRY(KeyTruncated, -346, "key truncated on index that disallows key truncation")
ESENT_ERR_ENTRY(DatabaseLeakInSpace, -348, "Some database pages have become unreachable even from the avail tree, only an offline defragmentation can return the lost space.")
ESENT_ERR_ENTRY(BadEmptyPage, -351, "Database corrupted. Searching an unexpectedly empty page.")
ESENT_WRN_ENTRY_SHORT(BTNotVisibleRejected, 352, "Current entry is not visible because it has been rejected by a move filter")
ESENT_WRN_ENTRY_SHORT(BTNotVisibleAccumulated, 353, "Current entry is not visible because it is being accumulated by a move filter")
ESENT_ERR_ENTRY(BadLineCount, -354, "Number of lines on the page is too few compared to the line being operated on")
//
// RECORD MANAGER errors
//
ESENT_WRN_ENTRY(SeparateLongValue, 406, "Column is a separated long-value")
ESENT_ALIASE_WRN_ENTRY(RecordFoundGreater, SeekNotEqual)
ESENT_ALIASE_WRN_ENTRY(RecordFoundLess, SeekNotEqual)
ESENT_ALIASE_ERR_ENTRY(ColumnIllegalNull, NullInvalid)
ESENT_ERR_ENTRY(KeyTooBig, -408, "Key is too large")
ESENT_ERR_ENTRY(CannotSeparateIntrinsicLV, -416, "illegal attempt to separate an LV which must be intrinsic")
ESENT_ERR_ENTRY(SeparatedLongValue, -421, "Operation not supported on separated long-value")
ESENT_ERR_ENTRY(MustBeSeparateLongValue, -423, "Can only preread long value columns that can be separate, e.g. not size constrained so that they are fixed or variable columns")
ESENT_ERR_ENTRY(InvalidPreread, -424, "Cannot preread long values when current index secondary")
//
// LOGGING/RECOVERY errors
//
ESENT_ERR_ENTRY(InvalidLoggedOperation, -500, "Logged operation cannot be redone")
ESENT_ERR_ENTRY(LogFileCorrupt, -501, "Log file is corrupt")
ESENT_ERR_ENTRY(NoBackupDirectory, -503, "No backup directory given")
ESENT_ERR_ENTRY(BackupDirectoryNotEmpty, -504, "The backup directory is not emtpy")
ESENT_ERR_ENTRY(BackupInProgress, -505, "Backup is active already")
ESENT_ERR_ENTRY(RestoreInProgress, -506, "Restore in progress")
ESENT_ERR_ENTRY(MissingPreviousLogFile, -509, "Missing the log file for check point")
ESENT_ERR_ENTRY(LogWriteFail, -510, "Failure writing to log file")
ESENT_ERR_ENTRY(LogDisabledDueToRecoveryFailure, -511, "Try to log something after recovery faild")
ESENT_ERR_ENTRY(CannotLogDuringRecoveryRedo, -512, "Try to log something during recovery redo")
ESENT_ERR_ENTRY(LogGenerationMismatch, -513, "Name of logfile does not match internal generation number")
ESENT_ERR_ENTRY(BadLogVersion, -514, "Version of log file is not compatible with Jet version")
ESENT_ERR_ENTRY(InvalidLogSequence, -515, "Timestamp in next log does not match expected")
ESENT_ERR_ENTRY(LoggingDisabled, -516, "Log is not active")
ESENT_ERR_ENTRY(LogBufferTooSmall, -517, "Log buffer is too small for recovery")
ESENT_ERR_ENTRY(LogSequenceEnd, -519, "Maximum log file number exceeded")
ESENT_ERR_ENTRY(NoBackup, -520, "No backup in progress")
ESENT_ERR_ENTRY(InvalidBackupSequence, -521, "Backup call out of sequence")
ESENT_ERR_ENTRY(BackupNotAllowedYet, -523, "Cannot do backup now")
ESENT_ERR_ENTRY(DeleteBackupFileFail, -524, "Could not delete backup file")
ESENT_ERR_ENTRY(MakeBackupDirectoryFail, -525, "Could not make backup temp directory")
ESENT_ERR_ENTRY(InvalidBackup, -526, "Cannot perform incremental backup when circular logging enabled")
ESENT_ERR_ENTRY(RecoveredWithErrors, -527, "Restored with errors")
ESENT_ERR_ENTRY(MissingLogFile, -528, "Current log file missing")
ESENT_ERR_ENTRY(LogDiskFull, -529, "Log disk full")
ESENT_ERR_ENTRY(BadLogSignature, -530, "Bad signature for a log file")
ESENT_ERR_ENTRY(BadDbSignature, -531, "Bad signature for a db file")
ESENT_ERR_ENTRY(BadCheckpointSignature, -532, "Bad signature for a checkpoint file")
ESENT_ERR_ENTRY(CheckpointCorrupt, -533, "Checkpoint file not found or corrupt")
ESENT_ERR_ENTRY(MissingPatchPage, -534, "Patch file page not found during recovery")
ESENT_ERR_ENTRY(BadPatchPage, -535, "Patch file page is not valid")
ESENT_ERR_ENTRY(RedoAbruptEnded, -536, "Redo abruptly ended due to sudden failure in reading logs from log file")
ESENT_ERR_ENTRY(PatchFileMissing, -538, "Hard restore detected that patch file is missing from backup set")
ESENT_ERR_ENTRY(DatabaseLogSetMismatch, -539, "Database does not belong with the current set of log files")
ESENT_ERR_ENTRY(DatabaseStreamingFileMismatch, -540, "Database and streaming file do not match each other")
ESENT_ERR_ENTRY(LogFileSizeMismatch, -541, "actual log file size does not match ESENT_paramLogFileSize")
ESENT_ERR_ENTRY(CheckpointFileNotFound, -542, "Could not locate checkpoint file")
ESENT_ERR_ENTRY(RequiredLogFilesMissing, -543, "The required log files for recovery is missing.")
ESENT_ERR_ENTRY(SoftRecoveryOnBackupDatabase, -544, "Soft recovery is intended on a backup database. Restore should be used instead")
ESENT_ERR_ENTRY(LogFileSizeMismatchDatabasesConsistent, -545, "databases have been recovered, but the log file size used during recovery does not match ESENT_paramLogFileSize")
ESENT_ERR_ENTRY(LogSectorSizeMismatch, -546, "the log file sector size does not match the current volume's sector size")
ESENT_ERR_ENTRY(LogSectorSizeMismatchDatabasesConsistent, -547, "databases have been recovered, but the log file sector size (used during recovery) does not match the current volume's sector size")
ESENT_ERR_ENTRY(LogSequenceEndDatabasesConsistent, -548, "databases have been recovered, but all possible log generations in the current sequence are used; delete all log files and the checkpoint file and backup the databases before continuing")
//
//
//
ESENT_ERR_ENTRY(StreamingDataNotLogged, -549, "Illegal attempt to replay a streaming file operation where the data wasn't logged. Probably caused by an attempt to roll-forward with circular logging enabled")
//
//
//
ESENT_ERR_ENTRY(DatabaseDirtyShutdown, -550, "Database was not shutdown cleanly. Recovery must first be run to properly complete database operations for the previous shutdown.")
ESENT_ALIASE_ERR_ENTRY(DatabaseInconsistent, DatabaseDirtyShutdown)
ESENT_ERR_ENTRY(ConsistentTimeMismatch, -551, "Database last consistent time unmatched")
ESENT_ERR_ENTRY(DatabasePatchFileMismatch, -552, "Patch file is not generated from this backup")
ESENT_ERR_ENTRY(EndingRestoreLogTooLow, -553, "The starting log number too low for the restore")
ESENT_ERR_ENTRY(StartingRestoreLogTooHigh, -554, "The starting log number too high for the restore")
ESENT_ERR_ENTRY(GivenLogFileHasBadSignature, -555, "Restore log file has bad signature")
ESENT_ERR_ENTRY(GivenLogFileIsNotContiguous, -556, "Restore log file is not contiguous")
ESENT_ERR_ENTRY(MissingRestoreLogFiles, -557, "Some restore log files are missing")
ESENT_WRN_ENTRY(ExistingLogFileHasBadSignature, 558, "Existing log file has bad signature")
ESENT_WRN_ENTRY(ExistingLogFileIsNotContiguous, 559, "Existing log file is not contiguous")
ESENT_ERR_ENTRY(MissingFullBackup, -560, "The database missed a previous full backup before incremental backup")
ESENT_ERR_ENTRY(BadBackupDatabaseSize, -561, "The backup database size is not in 4k")
ESENT_ERR_ENTRY(DatabaseAlreadyUpgraded, -562, "Attempted to upgrade a database that is already current")
ESENT_ERR_ENTRY(DatabaseIncompleteUpgrade, -563, "Attempted to use a database which was only partially converted to the current format -- must restore from backup")
ESENT_WRN_ENTRY(SkipThisRecord, 564, "INTERNAL ERROR")
ESENT_ERR_ENTRY(MissingCurrentLogFiles, -565, "Some current log files are missing for continuous restore")
//
//
//
ESENT_ERR_ENTRY(DbTimeTooOld, -566, "dbtime on page smaller than dbtimeBefore in record")
ESENT_ERR_ENTRY(DbTimeTooNew, -567, "dbtime on page in advance of the dbtimeBefore in record")
ESENT_ERR_ENTRY(MissingFileToBackup, -569, "Some log or patch files are missing during backup")
//
//
//
ESENT_ERR_ENTRY(LogTornWriteDuringHardRestore, -570, "torn-write was detected in a backup set during hard restore")
ESENT_ERR_ENTRY(LogTornWriteDuringHardRecovery, -571, "torn-write was detected during hard recovery (log was not part of a backup set)")
ESENT_ERR_ENTRY(LogCorruptDuringHardRestore, -573, "corruption was detected in a backup set during hard restore")
ESENT_ERR_ENTRY(LogCorruptDuringHardRecovery, -574, "corruption was detected during hard recovery (log was not part of a backup set)")
//
//
//
ESENT_ERR_ENTRY(MustDisableLoggingForDbUpgrade, -575, "Cannot have logging enabled while attempting to upgrade db")
//
//
//
ESENT_ERR_ENTRY(BadRestoreTargetInstance, -577, "TargetInstance specified for restore is not found or log files don't match")
ESENT_WRN_ENTRY(TargetInstanceRunning, 578, "TargetInstance specified for restore is running")
//
//
//
ESENT_ERR_ENTRY(RecoveredWithoutUndo, -579, "Soft recovery successfully replayed all operations, but the Undo phase of recovery was skipped")
//
//
//
ESENT_ERR_ENTRY(DatabasesNotFromSameSnapshot, -580, "Databases to be restored are not from the same shadow copy backup")
ESENT_ERR_ENTRY(SoftRecoveryOnSnapshot, -581, "Soft recovery on a database from a shadow copy backup set")
ESENT_ERR_ENTRY(CommittedLogFilesMissing, -582, "One or more logs that were committed to this database, are missing.These log files are required to maintain durable ACID semantics, but not required to maintain consistency if the ESENT_bitReplayIgnoreLostLogs bit is specified during recovery.")
ESENT_ERR_ENTRY(SectorSizeNotSupported, -583, "The physical sector size reported by the disk subsystem, is unsupported by ESE for a specific file type.")
ESENT_ERR_ENTRY(RecoveredWithoutUndoDatabasesConsistent, -584, "Soft recovery successfully replayed all operations and intended to skip the Undo phase of recovery, but the Undo phase was not required")
ESENT_WRN_ENTRY(CommittedLogFilesLost, 585, "One or more logs that were committed to this database, were not recovered.The database is still clean/consistent, as though the lost log's transactions were committed lazily (and lost).")
ESENT_ERR_ENTRY(CommittedLogFileCorrupt, -586, "One or more logs were found to be corrupt during recovery.These log files are required to maintain durable ACID semantics, but not required to maintain consistency if the ESENT_bitIgnoreLostLogs bit and ESENT_paramDeleteOutOfRangeLogs is specified during recovery.")
ESENT_WRN_ENTRY(CommittedLogFilesRemoved, 587, "One or more logs that were committed to this database, were no recovered.The database is still clean/consistent, as though the corrupted log's transactions were committed lazily (and lost).")
ESENT_WRN_ENTRY(FinishWithUndo, 588, "Signal used by clients to indicate JetInit() finished with undo")
ESENT_ERR_ENTRY(LogSequenceChecksumMismatch, -590, "The previous log's accumulated segment checksum doesn't match the next log")
//
//
//
ESENT_WRN_ENTRY(DatabaseRepaired, 595, "Database corruption has been repaired")
ESENT_ERR_ENTRY(PageInitializedMismatch, -596, "Database divergence mismatch. Page was uninitialized on remote node, but initialized on local node.")
//
//
//
ESENT_ERR_ENTRY(UnicodeTranslationBufferTooSmall, -601, "Unicode translation buffer too small")
ESENT_ERR_ENTRY(UnicodeTranslationFail, -602, "Unicode normalization failed")
ESENT_ERR_ENTRY(UnicodeNormalizationNotSupported, -603, "OS does not provide support for Unicode normalisation (and no normalisation callback was specified)")
ESENT_ERR_ENTRY(UnicodeLanguageValidationFailure, -604, "Can not validate the language")
//
//
//
ESENT_ERR_ENTRY(ExistingLogFileHasBadSignature, -610, "Existing log file has bad signature")
ESENT_ERR_ENTRY(ExistingLogFileIsNotContiguous, -611, "Existing log file is not contiguous")
//
//
//
ESENT_ERR_ENTRY(LogReadVerifyFailure, -612, "Checksum error in log file during backup")
//
//
//
ESENT_ERR_ENTRY(CheckpointDepthTooDeep, -614, "too many outstanding generations between checkpoint and current generation")
//
//
//
ESENT_ERR_ENTRY(RestoreOfNonBackupDatabase, -615, "hard recovery attempted on a database that wasn't a backup database")
ESENT_ERR_ENTRY(LogFileNotCopied, -616, "log truncation attempted but not all required logs were copied")
ESENT_ERR_ENTRY(TransactionTooLong, -618, "Too many outstanding generations between JetBeginTransaction and current generation.")
//
//
//
ESENT_ERR_ENTRY(EngineFormatVersionNoLongerSupportedTooLow, -619, "The specified ESENT_ENGINEFORMATVERSION value is too low to be supported by this version of ESE.")
ESENT_ERR_ENTRY(EngineFormatVersionNotYetImplementedTooHigh, -620, "The specified ESENT_ENGINEFORMATVERSION value is too high, higher than this version of ESE knows about.")
ESENT_ERR_ENTRY(EngineFormatVersionParamTooLowForRequestedFeature, -621, "Thrown by a format feature (not at JetSetSystemParameter) if the client requests a feature that requires a version higher than that set for the ESENT_paramEngineFormatVersion.")
ESENT_ERR_ENTRY(EngineFormatVersionSpecifiedTooLowForLogVersion, -622, "The specified ESENT_ENGINEFORMATVERSION is set too low for this log stream, the log files have already been upgraded to a higher version.A higher ESENT_ENGINEFORMATVERSION value must be set in the param.")
ESENT_ERR_ENTRY(EngineFormatVersionSpecifiedTooLowForDatabaseVersion, -623, "The specified ESENT_ENGINEFORMATVERSION is set too low for this database file, the database file has already been upgraded to a higher version.A higher ESENT_ENGINEFORMATVERSION value must be set in the param.")
//
//
//
ESENT_ERR_ENTRY(BackupAbortByServer, -801, "Backup was aborted by server by calling JetTerm with ESENT_bitTermStopBackup or by calling JetStopBackup")
//
//
//
ESENT_ERR_ENTRY(InvalidGrbit, -900, "Invalid flags parameter")
//
//
//
ESENT_ERR_ENTRY(TermInProgress, -1000, "Termination in progress")
ESENT_ERR_ENTRY(FeatureNotAvailable, -1001, "API not supported")
ESENT_ERR_ENTRY(InvalidName, -1002, "Invalid name")
ESENT_ERR_ENTRY(InvalidParameter, -1003, "Invalid API parameter")
ESENT_WRN_ENTRY(ColumnNull, 1004, "Column is NULL-valued")
ESENT_WRN_ENTRY(BufferTruncated, 1006, "Buffer too small for data")
ESENT_WRN_ENTRY(DatabaseAttached, 1007, "Database is already attached")
ESENT_ERR_ENTRY(DatabaseFileReadOnly, -1008, "Tried to attach a read-only database file for read/write operations")
ESENT_WRN_ENTRY(SortOverflow, 1009, "Sort does not fit in memory")
ESENT_ERR_ENTRY(InvalidDatabaseId, -1010, "Invalid database id")
ESENT_ERR_ENTRY(OutOfMemory, -1011, "Out of Memory")
ESENT_ERR_ENTRY(OutOfDatabaseSpace, -1012, "Maximum database size reached")
ESENT_ERR_ENTRY(OutOfCursors, -1013, "Out of table cursors")
ESENT_ERR_ENTRY(OutOfBuffers, -1014, "Out of database page buffers")
ESENT_ERR_ENTRY(TooManyIndexes, -1015, "Too many indexes")
ESENT_ERR_ENTRY(TooManyKeys, -1016, "Too many columns in an index")
ESENT_ERR_ENTRY(RecordDeleted, -1017, "Record has been deleted")
ESENT_ERR_ENTRY(ReadVerifyFailure, -1018, "Checksum error on a database page")
ESENT_ERR_ENTRY(PageNotInitialized, -1019, "Blank database page")
ESENT_ERR_ENTRY(OutOfFileHandles, -1020, "Out of file handles")
ESENT_ERR_ENTRY(DiskReadVerificationFailure, -1021, "The OS returned ERROR_CRC from file IO")
ESENT_ERR_ENTRY(DiskIO, -1022, "Disk IO error")
ESENT_ERR_ENTRY(InvalidPath, -1023, "Invalid file path")
ESENT_ERR_ENTRY(InvalidSystemPath, -1024, "Invalid system path")
ESENT_ERR_ENTRY(InvalidLogDirectory, -1025, "Invalid log directory")
ESENT_ERR_ENTRY(RecordTooBig, -1026, "Record larger than maximum size")
ESENT_ERR_ENTRY(TooManyOpenDatabases, -1027, "Too many open databases")
ESENT_ERR_ENTRY(InvalidDatabase, -1028, "Not a database file")
ESENT_ERR_ENTRY(NotInitialized, -1029, "Database engine not initialized")
ESENT_ERR_ENTRY(AlreadyInitialized, -1030, "Database engine already initialized")
ESENT_ERR_ENTRY(InitInProgress, -1031, "Database engine is being initialized")
ESENT_ERR_ENTRY(FileAccessDenied, -1032, "Cannot access file, the file is locked or in use")
ESENT_ERR_ENTRY(BufferTooSmall, -1038, "Buffer is too small")
ESENT_WRN_ENTRY(SeekNotEqual, 1039, "Exact match not found during seek")
ESENT_ERR_ENTRY(TooManyColumns, -1040, "Too many columns defined")
ESENT_ERR_ENTRY(ContainerNotEmpty, -1043, "Container is not empty")
ESENT_ERR_ENTRY(InvalidFilename, -1044, "Filename is invalid")
ESENT_ERR_ENTRY(InvalidBookmark, -1045, "Invalid bookmark")
ESENT_ERR_ENTRY(ColumnInUse, -1046, "Column used in an index")
ESENT_ERR_ENTRY(InvalidBufferSize, -1047, "Data buffer doesn't match column size")
ESENT_ERR_ENTRY(ColumnNotUpdatable, -1048, "Cannot set column value")
ESENT_ERR_ENTRY(IndexInUse, -1051, "Index is in use")
ESENT_ERR_ENTRY(LinkNotSupported, -1052, "Link support unavailable")
ESENT_ERR_ENTRY(NullKeyDisallowed, -1053, "Null keys are disallowed on index")
ESENT_ERR_ENTRY(NotInTransaction, -1054, "Operation must be within a transaction")
ESENT_WRN_ENTRY(NoErrorInfo, 1055, "No extended error information")
ESENT_ERR_ENTRY(MustRollback, -1057, "Transaction must rollback because failure of unversioned update")
ESENT_WRN_ENTRY(NoIdleActivity, 1058, "No idle activity occured")
ESENT_ERR_ENTRY(TooManyActiveUsers, -1059, "Too many active database users")
ESENT_ERR_ENTRY(InvalidCountry, -1061, "Invalid or unknown country/region code")
ESENT_ERR_ENTRY(InvalidLanguageId, -1062, "Invalid or unknown language id")
ESENT_ERR_ENTRY(InvalidCodePage, -1063, "Invalid or unknown code page")
ESENT_ERR_ENTRY(InvalidLCMapStringFlags, -1064, "Invalid flags for LCMapString()")
ESENT_ERR_ENTRY(VersionStoreEntryTooBig, -1065, "Attempted to create a version store entry (RCE) larger than a version bucket")
ESENT_ERR_ENTRY(VersionStoreOutOfMemoryAndCleanupTimedOut, -1066, "Version store out of memory (and cleanup attempt failed to complete)")
ESENT_WRN_ENTRY(NoWriteLock, 1067, "No write lock at transaction level 0")
ESENT_WRN_ENTRY(ColumnSetNull, 1068, "Column set to NULL-value")
ESENT_ERR_ENTRY(VersionStoreOutOfMemory, -1069, "Version store out of memory (cleanup already attempted)")
ESENT_ERR_ENTRY(CannotIndex, -1071, "Cannot index escrow column")
ESENT_ERR_ENTRY(RecordNotDeleted, -1072, "Record has not been deleted")
ESENT_ERR_ENTRY(TooManyMempoolEntries, -1073, "Too many mempool entries requested")
ESENT_ERR_ENTRY(OutOfObjectIDs, -1074, "Out of btree ObjectIDs (perform offline defrag to reclaim freed/unused ObjectIds)")
ESENT_ERR_ENTRY(OutOfLongValueIDs, -1075, "Long-value ID counter has reached maximum value. (perform offline defrag to reclaim free/unused LongValueIDs)")
ESENT_ERR_ENTRY(OutOfAutoincrementValues, -1076, "Auto-increment counter has reached maximum value (offline defrag WILL NOT be able to reclaim free/unused Auto-increment values).")
ESENT_ERR_ENTRY(OutOfDbtimeValues, -1077, "Dbtime counter has reached maximum value (perform offline defrag to reclaim free/unused Dbtime values)")
ESENT_ERR_ENTRY(OutOfSequentialIndexValues, -1078, "Sequential index counter has reached maximum value (perform offline defrag to reclaim free/unused SequentialIndex values)")
//
//
//
ESENT_ERR_ENTRY(RunningInOneInstanceMode, -1080, "Multi-instance call with single-instance mode enabled")
ESENT_ERR_ENTRY(RunningInMultiInstanceMode, -1081, "Single-instance call with multi-instance mode enabled")
ESENT_ERR_ENTRY(SystemParamsAlreadySet, -1082, "Global system parameters have already been set")
//
//
//
ESENT_ERR_ENTRY(SystemPathInUse, -1083, "System path already used by another database instance")
ESENT_ERR_ENTRY(LogFilePathInUse, -1084, "Logfile path already used by another database instance")
ESENT_ERR_ENTRY(TempPathInUse, -1085, "Temp path already used by another database instance")
ESENT_ERR_ENTRY(InstanceNameInUse, -1086, "Instance Name already in use")
ESENT_ERR_ENTRY(SystemParameterConflict, -1087, "Global system parameters have already been set, but to a conflicting or disagreeable state to the specified values.")
//
//
//
ESENT_ERR_ENTRY(InstanceUnavailable, -1090, "This instance cannot be used because it encountered a fatal error")
ESENT_ERR_ENTRY(DatabaseUnavailable, -1091, "This database cannot be used because it encountered a fatal error")
ESENT_ERR_ENTRY(InstanceUnavailableDueToFatalLogDiskFull, -1092, "This instance cannot be used because it encountered a log-disk-full error performing an operation (likely transaction rollback) that could not tolerate failure")
ESENT_ERR_ENTRY(InvalidSesparamId, -1093, "This ESENT_sesparam* identifier is not known to the ESE engine.")
//
//
//
ESENT_ERR_ENTRY(TooManyRecords, -1094, "There are too many records to enumerate, switch to an API that handles 64-bit numbers")
//
//
//
ESENT_ERR_ENTRY(InvalidDbparamId, -1095, "This ESENT_dbparam* identifier is not known to the ESE engine.")
//
//
//
ESENT_ERR_ENTRY(OutOfSessions, -1101, "Out of sessions")
ESENT_ERR_ENTRY(WriteConflict, -1102, "Write lock failed due to outstanding write lock")
ESENT_ERR_ENTRY(TransTooDeep, -1103, "Transactions nested too deeply")
ESENT_ERR_ENTRY(InvalidSesid, -1104, "Invalid session handle")
ESENT_ERR_ENTRY(WriteConflictPrimaryIndex, -1105, "Update attempted on uncommitted primary index")
ESENT_ERR_ENTRY(InTransaction, -1108, "Operation not allowed within a transaction")
ESENT_ERR_ENTRY(RollbackRequired, -1109, "Must rollback current transaction -- cannot commit or begin a new one")
ESENT_ERR_ENTRY(TransReadOnly, -1110, "Read-only transaction tried to modify the database")
ESENT_ERR_ENTRY(SessionWriteConflict, -1111, "Attempt to replace the same record by two diffrerent cursors in the same session")
//
//
//
ESENT_ERR_ENTRY(RecordTooBigForBackwardCompatibility, -1112, "record would be too big if represented in a database format from a previous version of Jet")
ESENT_ERR_ENTRY(CannotMaterializeForwardOnlySort, -1113, "The temp table could not be created due to parameters that conflict with ESENT_bitTTForwardOnly")
//
//
//
ESENT_ERR_ENTRY(SesidTableIdMismatch, -1114, "This session handle can't be used with this table id")
ESENT_ERR_ENTRY(InvalidInstance, -1115, "Invalid instance handle")
ESENT_ERR_ENTRY(DirtyShutdown, -1116, "The instance was shutdown successfully but all the attached databases were left in a dirty state by request via ESENT_bitTermDirty")
//
// unused -1117
//
ESENT_ERR_ENTRY(ReadPgnoVerifyFailure, -1118, "The database page read from disk had the wrong page number.")
ESENT_ERR_ENTRY(ReadLostFlushVerifyFailure, -1119, "The database page read from disk had a previous write not represented on the page.")
ESENT_ERR_ENTRY(FileSystemCorruption, -1121, "File system operation failed with an error indicating the file system is corrupt.")
ESENT_WRN_ENTRY(ShrinkNotPossible, 1122, "Database file could not be shrunk because there is not enough internal free space available or there is unmovable data present.")
ESENT_ERR_ENTRY(RecoveryVerifyFailure, -1123, "One or more database pages read from disk during recovery do not match the expected state.")
//
//
//
ESENT_ERR_ENTRY(FilteredMoveNotSupported, -1124, "Attempted to provide a filter to JetSetCursorFilter() in an unsupported scenario.")
//
//
//
ESENT_ERR_ENTRY(DatabaseDuplicate, -1201, "Database already exists")
ESENT_ERR_ENTRY(DatabaseInUse, -1202, "Database in use")
ESENT_ERR_ENTRY(DatabaseNotFound, -1203, "No such database")
ESENT_ERR_ENTRY(DatabaseInvalidName, -1204, "Invalid database name")
ESENT_ERR_ENTRY(DatabaseInvalidPages, -1205, "Invalid number of pages")
ESENT_ERR_ENTRY(DatabaseCorrupted, -1206, "Non database file or corrupted db")
ESENT_ERR_ENTRY(DatabaseLocked, -1207, "Database exclusively locked")
ESENT_ERR_ENTRY(CannotDisableVersioning, -1208, "Cannot disable versioning for this database")
ESENT_ERR_ENTRY(InvalidDatabaseVersion, -1209, "Database engine is incompatible with database")
//
//
//
ESENT_ERR_ENTRY(Database200Format, -1210, "The database is in an older (200) format")
ESENT_ERR_ENTRY(Database400Format, -1211, "The database is in an older (400) format")
ESENT_ERR_ENTRY(Database500Format, -1212, "The database is in an older (500) format")
//
//
//
ESENT_ERR_ENTRY(PageSizeMismatch, -1213, "The database page size does not match the engine")
ESENT_ERR_ENTRY(TooManyInstances, -1214, "Cannot start any more database instances")
ESENT_ERR_ENTRY(DatabaseSharingViolation, -1215, "A different database instance is using this database")
ESENT_ERR_ENTRY(AttachedDatabaseMismatch, -1216, "An outstanding database attachment has been detected at the start or end of recovery, but database is missing or does not match attachment info")
ESENT_ERR_ENTRY(DatabaseInvalidPath, -1217, "Specified path to database file is illegal")
ESENT_ERR_ENTRY(DatabaseIdInUse, -1218, "A database is being assigned an id already in use")
ESENT_ERR_ENTRY(ForceDetachNotAllowed, -1219, "Force Detach allowed only after normal detach errored out")
ESENT_ERR_ENTRY(CatalogCorrupted, -1220, "Corruption detected in catalog")
ESENT_ERR_ENTRY(PartiallyAttachedDB, -1221, "Database is partially attached. Cannot complete attach operation")
ESENT_ERR_ENTRY(DatabaseSignInUse, -1222, "Database with same signature in use")
//
//
//
ESENT_ERR_ENTRY(DatabaseCorruptedNoRepair, -1224, "Corrupted db but repair not allowed")
ESENT_ERR_ENTRY(InvalidCreateDbVersion, -1225, "recovery tried to replay a database creation, but the database was originally created with an incompatible (likely older) version of the database engine")
//
//
//
ESENT_ERR_ENTRY(DatabaseNotReady, -1230, "Recovery on this database has not yet completed enough to permit access.")
ESENT_ERR_ENTRY(DatabaseAttachedForRecovery, -1231, "Database is attached but only for recovery.It must be explicitly attached before it can be opened. ")
ESENT_ERR_ENTRY(TransactionsNotReadyDuringRecovery, -1232, "Recovery has not seen any Begin0/Commit0 records and so does not know what trxBegin0 to assign to this transaction")
//
//
//
ESENT_WRN_ENTRY(TableEmpty, 1301, "Opened an empty table")
ESENT_ERR_ENTRY(TableLocked, -1302, "Table is exclusively locked")
ESENT_ERR_ENTRY(TableDuplicate, -1303, "Table already exists")
ESENT_ERR_ENTRY(TableInUse, -1304, "Table is in use, cannot lock")
ESENT_ERR_ENTRY(ObjectNotFound, -1305, "No such table or object")
ESENT_ERR_ENTRY(DensityInvalid, -1307, "Bad file/index density")
ESENT_ERR_ENTRY(TableNotEmpty, -1308, "Table is not empty")
ESENT_ERR_ENTRY(InvalidTableId, -1310, "Invalid table id")
ESENT_ERR_ENTRY(TooManyOpenTables, -1311, "Cannot open any more tables (cleanup already attempted)")
ESENT_ERR_ENTRY(IllegalOperation, -1312, "Oper. not supported on table")
ESENT_ERR_ENTRY(TooManyOpenTablesAndCleanupTimedOut, -1313, "Cannot open any more tables (cleanup attempt failed to complete)")
ESENT_ERR_ENTRY(ObjectDuplicate, -1314, "Table or object name in use")
ESENT_ERR_ENTRY(InvalidObject, -1316, "Object is invalid for operation")
ESENT_ERR_ENTRY(CannotDeleteTempTable, -1317, "Use CloseTable instead of DeleteTable to delete temp table")
ESENT_ERR_ENTRY(CannotDeleteSystemTable, -1318, "Illegal attempt to delete a system table")
ESENT_ERR_ENTRY(CannotDeleteTemplateTable, -1319, "Illegal attempt to delete a template table")
ESENT_ERR_ENTRY(ExclusiveTableLockRequired, -1322, "Must have exclusive lock on table.")
ESENT_ERR_ENTRY(FixedDDL, -1323, "DDL operations prohibited on this table")
ESENT_ERR_ENTRY(FixedInheritedDDL, -1324, "On a derived table, DDL operations are prohibited on inherited portion of DDL")
ESENT_ERR_ENTRY(CannotNestDDL, -1325, "Nesting of hierarchical DDL is not currently supported.")
ESENT_ERR_ENTRY(DDLNotInheritable, -1326, "Tried to inherit DDL from a table not marked as a template table.")
ESENT_WRN_ENTRY(TableInUseBySystem, 1327, "System cleanup has a cursor open on the table")
ESENT_ERR_ENTRY(InvalidSettings, -1328, "System parameters were set improperly")
ESENT_ERR_ENTRY(ClientRequestToStopJetService, -1329, "Client has requested stop service")
ESENT_ERR_ENTRY(CannotAddFixedVarColumnToDerivedTable, -1330, "Template table was created with NoFixedVarColumnsInDerivedTables")
//
//DDL errors
//
// Note: Some DDL errors have snuck into other categories.
//
ESENT_ERR_ENTRY(IndexCantBuild, -1401, "Index build failed")
ESENT_ERR_ENTRY(IndexHasPrimary, -1402, "Primary index already defined")
ESENT_ERR_ENTRY(IndexDuplicate, -1403, "Index is already defined")
ESENT_ERR_ENTRY(IndexNotFound, -1404, "No such index")
ESENT_ERR_ENTRY(IndexMustStay, -1405, "Cannot delete clustered index")
ESENT_ERR_ENTRY(IndexInvalidDef, -1406, "Illegal index definition")
ESENT_ERR_ENTRY(InvalidCreateIndex, -1409, "Invalid create index description")
ESENT_ERR_ENTRY(TooManyOpenIndexes, -1410, "Out of index description blocks")
ESENT_ERR_ENTRY(MultiValuedIndexViolation, -1411, "Non-unique inter-record index keys generated for a multivalued index")
ESENT_ERR_ENTRY(IndexBuildCorrupted, -1412, "Failed to build a secondary index that properly reflects primary index")
ESENT_ERR_ENTRY(PrimaryIndexCorrupted, -1413, "Primary index is corrupt. The database must be defragmented or the table deleted.")
ESENT_ERR_ENTRY(SecondaryIndexCorrupted, -1414, "Secondary index is corrupt. The database must be defragmented or the affected index must be deleted. If the corrupt index is over Unicode text, a likely cause is a sort-order change.")
ESENT_WRN_ENTRY(CorruptIndexDeleted, 1415, "Out of date index removed")
ESENT_ERR_ENTRY(InvalidIndexId, -1416, "Illegal index id")
ESENT_WRN_ENTRY(PrimaryIndexOutOfDate, 1417, "The Primary index is created with an incompatible OS sort version. The table can not be safely modified.")
ESENT_WRN_ENTRY(SecondaryIndexOutOfDate, 1418, "One or more Secondary index is created with an incompatible OS sort version. Any index over Unicode text should be deleted.")
//
//
//
ESENT_ERR_ENTRY(IndexTuplesSecondaryIndexOnly, -1430, "tuple index can only be on a secondary index")
ESENT_ERR_ENTRY(IndexTuplesTooManyColumns, -1431, "tuple index may only have eleven columns in the index")
ESENT_ALIASE_ERR_ENTRY(IndexTuplesOneColumnOnly, IndexTuplesTooManyColumns)
ESENT_ERR_ENTRY(IndexTuplesNonUniqueOnly, -1432, "tuple index must be a non-unique index")
ESENT_ERR_ENTRY(IndexTuplesTextBinaryColumnsOnly, -1433, "tuple index must be on a text/binary column")
ESENT_ALIASE_ERR_ENTRY(IndexTuplesTextColumnsOnly, IndexTuplesTextBinaryColumnsOnly)
ESENT_ERR_ENTRY(IndexTuplesVarSegMacNotAllowed, -1434, "tuple index does not allow setting cbVarSegMac")
ESENT_ERR_ENTRY(IndexTuplesInvalidLimits, -1435, "invalid min/max tuple length or max characters to index specified")
ESENT_ERR_ENTRY(IndexTuplesCannotRetrieveFromIndex, -1436, "cannot call RetrieveColumn() with RetrieveFromIndex on a tuple index")
ESENT_ERR_ENTRY(IndexTuplesKeyTooSmall, -1437, "specified key does not meet minimum tuple length")
ESENT_ERR_ENTRY(InvalidLVChunkSize, -1438, "Specified LV chunk size is not supported")
ESENT_ERR_ENTRY(ColumnCannotBeEncrypted, -1439, "Only ESENT_coltypLongText and ESENT_coltypLongBinary columns without default values can be encrypted")
ESENT_ERR_ENTRY(CannotIndexOnEncryptedColumn, -1440, "Cannot index encrypted column")
//
//
//
ESENT_ERR_ENTRY(ColumnLong, -1501, "Column value is long")
ESENT_ERR_ENTRY(ColumnNoChunk, -1502, "No such chunk in long value")
ESENT_ERR_ENTRY(ColumnDoesNotFit, -1503, "Field will not fit in record")
ESENT_ERR_ENTRY(NullInvalid, -1504, "Null not valid")
ESENT_ERR_ENTRY(ColumnIndexed, -1505, "Column indexed, cannot delete")
ESENT_ERR_ENTRY(ColumnTooBig, -1506, "Field length is greater than maximum")
ESENT_ERR_ENTRY(ColumnNotFound, -1507, "No such column")
ESENT_ERR_ENTRY(ColumnDuplicate, -1508, "Field is already defined")
ESENT_ERR_ENTRY(MultiValuedColumnMustBeTagged, -1509, "Attempted to create a multi-valued column, but column was not Tagged")
ESENT_ERR_ENTRY(ColumnRedundant, -1510, "Second autoincrement or version column")
ESENT_ERR_ENTRY(InvalidColumnType, -1511, "Invalid column data type")
ESENT_WRN_ENTRY(ColumnMaxTruncated, 1512, "Max length too big, truncated")
ESENT_ERR_ENTRY(TaggedNotNULL, -1514, "No non-NULL tagged columns")
ESENT_ERR_ENTRY(NoCurrentIndex, -1515, "Invalid w/o a current index")
ESENT_ERR_ENTRY(KeyIsMade, -1516, "The key is completely made")
ESENT_ERR_ENTRY(BadColumnId, -1517, "Column Id Incorrect")
ESENT_ERR_ENTRY(BadItagSequence, -1518, "Bad itagSequence for tagged column")
ESENT_ERR_ENTRY(ColumnInRelationship, -1519, "Cannot delete, column participates in relationship")
ESENT_WRN_ENTRY(CopyLongValue, 1520, "Single instance column bursted")
ESENT_ERR_ENTRY(CannotBeTagged, -1521, "AutoIncrement and Version cannot be tagged")
ESENT_ERR_ENTRY(DefaultValueTooBig, -1524, "Default value exceeds maximum size")
ESENT_ERR_ENTRY(MultiValuedDuplicate, -1525, "Duplicate detected on a unique multi-valued column")
ESENT_ERR_ENTRY(LVCorrupted, -1526, "Corruption encountered in long-value tree")
ESENT_ERR_ENTRY(MultiValuedDuplicateAfterTruncation, -1528, "Duplicate detected on a unique multi-valued column after data was normalized, and normalizing truncated the data before comparison")
ESENT_ERR_ENTRY(DerivedColumnCorruption, -1529, "Invalid column in derived table")
ESENT_ERR_ENTRY(InvalidPlaceholderColumn, -1530, "Tried to convert column to a primary index placeholder, but column doesn't meet necessary criteria")
ESENT_WRN_ENTRY(ColumnSkipped, 1531, "Column value(s) not returned because the corresponding column id or itagSequence requested for enumeration was null")
ESENT_WRN_ENTRY(ColumnNotLocal, 1532, "Column value(s) not returned because they could not be reconstructed from the data at hand")
ESENT_WRN_ENTRY(ColumnMoreTags, 1533, "Column values exist that were not requested for enumeration")
ESENT_WRN_ENTRY(ColumnTruncated, 1534, "Column value truncated at the requested size limit during enumeration")
ESENT_WRN_ENTRY(ColumnPresent, 1535, "Column values exist but were not returned by request")
ESENT_WRN_ENTRY(ColumnSingleValue, 1536, "Column value returned in ESENT_COLUMNENUM as a result of ESENT_bitEnumerateCompressOutput")
ESENT_WRN_ENTRY(ColumnDefault, 1537, "Column value(s) not returned because they were set to their default value(s) and ESENT_bitEnumerateIgnoreDefault was specified")
ESENT_ERR_ENTRY(ColumnCannotBeCompressed, -1538, "Only ESENT_coltypLongText and ESENT_coltypLongBinary columns can be compressed")
ESENT_WRN_ENTRY(ColumnNotInRecord, 1539, "Column value(s) not returned because they could not be reconstructed from the data in the record")
ESENT_ERR_ENTRY(ColumnNoEncryptionKey, -1540, "Cannot retrieve/set encrypted column without an encryption key")
ESENT_WRN_ENTRY(ColumnReference, 1541, "Column value returned as a reference because it could not be reconstructed from the data in the record")
//
//
//
ESENT_ERR_ENTRY(RecordNotFound, -1601, "The key was not found")
ESENT_ERR_ENTRY(RecordNoCopy, -1602, "No working buffer")
ESENT_ERR_ENTRY(NoCurrentRecord, -1603, "Currency not on a record")
ESENT_ERR_ENTRY(RecordPrimaryChanged, -1604, "Primary key may not change")
ESENT_ERR_ENTRY(KeyDuplicate, -1605, "Illegal duplicate key")
ESENT_ERR_ENTRY(AlreadyPrepared, -1607, "Attempted to update record when record update was already in progress")
ESENT_ERR_ENTRY(KeyNotMade, -1608, "No call to JetMakeKey")
ESENT_ERR_ENTRY(UpdateNotPrepared, -1609, "No call to JetPrepareUpdate")
ESENT_WRN_ENTRY(DataHasChanged, 1610, "Data has changed")
ESENT_ERR_ENTRY(DataHasChanged, -1611, "Data has changed, operation aborted")
ESENT_WRN_ENTRY(KeyChanged, 1618, "Moved to new key")
ESENT_ERR_ENTRY(LanguageNotSupported, -1619, "Windows installation does not support language")
ESENT_ERR_ENTRY(DecompressionFailed, -1620, "Internal error: data could not be decompressed")
ESENT_ERR_ENTRY(UpdateMustVersion, -1621, "No version updates only for uncommitted tables")
ESENT_ERR_ENTRY(DecryptionFailed, -1622, "Data could not be decrypted")
ESENT_ERR_ENTRY(EncryptionBadItag, -1623, "Cannot encrypt tagged columns with itag>1")
//
//
//
ESENT_ERR_ENTRY(TooManySorts, -1701, "Too many sort processes")
ESENT_ERR_ENTRY(InvalidOnSort, -1702, "Invalid operation on Sort")
//
//
//
ESENT_ERR_ENTRY(TempFileOpenError, -1803, "Temp file could not be opened")
ESENT_ERR_ENTRY(TooManyAttachedDatabases, -1805, "Too many open databases")
ESENT_ERR_ENTRY(DiskFull, -1808, "No space left on disk")
ESENT_ERR_ENTRY(PermissionDenied, -1809, "Permission denied")
ESENT_ERR_ENTRY(FileNotFound, -1811, "File not found")
ESENT_ERR_ENTRY(FileInvalidType, -1812, "Invalid file type")
ESENT_WRN_ENTRY(FileOpenReadOnly, 1813, "Database file is read only")
ESENT_ERR_ENTRY(FileAlreadyExists, -1814, "File already exists")
//
//
//
ESENT_ERR_ENTRY(AfterInitialization, -1850, "Cannot Restore after init.")
ESENT_ERR_ENTRY(LogCorrupted, -1852, "Logs could not be interpreted")
//
//
//
ESENT_ERR_ENTRY(InvalidOperation, -1906, "Invalid operation")
ESENT_ERR_ENTRY(AccessDenied, -1907, "Access denied")
ESENT_WRN_ENTRY(IdleFull, 1908, "Idle registry full")
ESENT_ERR_ENTRY(TooManySplits, -1909, "Infinite split")
ESENT_ERR_ENTRY(SessionSharingViolation, -1910, "Multiple threads are using the same session")
ESENT_ERR_ENTRY(EntryPointNotFound, -1911, "An entry point in a DLL we require could not be found")
ESENT_ERR_ENTRY(SessionContextAlreadySet, -1912, "Specified session already has a session context set")
ESENT_ERR_ENTRY(SessionContextNotSetByThisThread, -1913, "Tried to reset session context, but current thread did not orignally set the session context")
ESENT_ERR_ENTRY(SessionInUse, -1914, "Tried to terminate session in use")
ESENT_ERR_ENTRY(RecordFormatConversionFailed, -1915, "Internal error during dynamic record format conversion")
ESENT_ERR_ENTRY(OneDatabasePerSession, -1916, "Just one open user database per session is allowed (ESENT_paramOneDatabasePerSession)")
ESENT_ERR_ENTRY(RollbackError, -1917, "error during rollback")
ESENT_ERR_ENTRY(FlushMapVersionUnsupported, -1918, "The version of the persisted flush map is not supported by this version of the engine.")
ESENT_ERR_ENTRY(FlushMapDatabaseMismatch, -1919, "The persisted flush map and the database do not match.")
ESENT_ERR_ENTRY(FlushMapUnrecoverable, -1920, "The persisted flush map cannot be reconstructed.")
//
//
//
ESENT_WRN_ENTRY(DefragAlreadyRunning, 2000, "Online defrag already running on specified database")
ESENT_WRN_ENTRY(DefragNotRunning, 2001, "Online defrag not running on specified database")
ESENT_ERR_ENTRY(DatabaseAlreadyRunningMaintenance, -2004, "The operation did not complete successfully because the database is already running maintenance on specified database")
//
//
//
ESENT_WRN_ENTRY(CallbackNotRegistered, 2100, "Unregistered a non-existant callback function")
ESENT_ERR_ENTRY(CallbackFailed, -2101, "A callback failed")
ESENT_ERR_ENTRY(CallbackNotResolved, -2102, "A callback function could not be found")
//
//
//
ESENT_ERR_ENTRY(SpaceHintsInvalid, -2103, "An element of the JET space hints structure was not correct or actionable.")
//
//
//
ESENT_ERR_ENTRY(OSSnapshotInvalidSequence, -2401, "OS Shadow copy API used in an invalid sequence")
ESENT_ERR_ENTRY(OSSnapshotTimeOut, -2402, "OS Shadow copy ended with time-out")
ESENT_ERR_ENTRY(OSSnapshotNotAllowed, -2403, "OS Shadow copy not allowed (backup or recovery in progress)")
ESENT_ERR_ENTRY(OSSnapshotInvalidSnapId, -2404, "invalid ESENT_OSSNAPID")
//
//
//
ESENT_ERR_ENTRY(LSCallbackNotSpecified, -3000, "Attempted to use Local Storage without a callback function being specified")
ESENT_ERR_ENTRY(LSAlreadySet, -3001, "Attempted to set Local Storage for an object which already had it set")
ESENT_ERR_ENTRY(LSNotSet, -3002, "Attempted to retrieve Local Storage from an object which didn't have it set")
//
//
//
ESENT_ERR_ENTRY(FileIOSparse, -4000, "an I/O was issued to a location that was sparse")
ESENT_ERR_ENTRY(FileIOBeyondEOF, -4001, "a read was issued to a location beyond EOF (writes will expand the file)")
ESENT_ERR_ENTRY(FileIOAbort, -4002, "instructs the ESENT_ABORTRETRYFAILCALLBACK caller to abort the specified I/O")
ESENT_ERR_ENTRY(FileIORetry, -4003, "instructs the ESENT_ABORTRETRYFAILCALLBACK caller to retry the specified I/O")
ESENT_ERR_ENTRY(FileIOFail, -4004, "instructs the ESENT_ABORTRETRYFAILCALLBACK caller to fail the specified I/O")
ESENT_ERR_ENTRY(FileCompressed, -4005, "read/write access is not supported on compressed files")
