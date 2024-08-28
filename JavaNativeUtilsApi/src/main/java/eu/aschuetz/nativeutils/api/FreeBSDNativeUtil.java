package eu.aschuetz.nativeutils.api;

import eu.aschuetz.nativeutils.api.exceptions.FileIsDirectoryException;
import eu.aschuetz.nativeutils.api.exceptions.QuotaExceededException;
import eu.aschuetz.nativeutils.api.exceptions.ResourceBusyException;
import eu.aschuetz.nativeutils.api.exceptions.UnknownNativeErrorException;
import eu.aschuetz.nativeutils.api.structs.Stat;

import java.io.FileNotFoundException;
import java.io.IOException;
import java.nio.file.*;

public interface FreeBSDNativeUtil extends PosixNativeUtil {

}
