// //////////////////////////////////////////////////////////////////////////////////////
//
//    Copyright 2022 James Patrick Norris
//
//    This file is part of DiaperGlu v5.5.
//
//    DiaperGlu v5.5 is free software; you can redistribute it and/or modify
//    it under the terms of the GNU General Public License as published by
//    the Free Software Foundation; either version 2 of the License, or
//    (at your option) any later version.
//
//    DiaperGlu v5.5 is distributed in the hope that it will be useful,
//    but WITHOUT ANY WARRANTY; without even the implied warranty of
//    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//    GNU General Public License for more details.
//
//    You should have received a copy of the GNU General Public License
//    along with DiaperGlu v5.5; if not, write to the Free Software
//    Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
//
// //////////////////////////////////////////////////////////////////////////////////////

// /////////////////////////////
// James Patrick Norris       //
// www.rainbarrel.com         //
// July 2, 2022               //
// version 5.5                //
// /////////////////////////////


#include "diapergluforth.h"

FLOAT64 dg_testreturndfp () {
    return (2.0);
}
  
const char* dg_evaluatebuffername = "dg_evaluatebuffer";

void dg_evaluatebuffersub (
    Bufferhandle* pBHarrayhead,
    UINT64 bufferid)
{
    unsigned char* pbuffer;
    UINT64* pbufferlength;

    UINT64* pbufferoffset;

    UINT64 beginoffset;
    UINT64 namelength;

    UINT64 number;
    UINT64 flag;

    UINT64 definition;

    unsigned char* pname;
    const char* pstate;

    UINT64 base;

    UINT64 u;
    FLOAT64 fnumber; 
    UINT64 x;  


    Bufferhandle* pBH;

    UINT64 olderrorcount = dg_geterrorcount(pBHarrayhead);
    
    if (baderrorcount == olderrorcount)
    {
        return;
    }
    
    pbuffer = dg_getpbuffer(
        pBHarrayhead,
        bufferid,
        &pbufferlength);

    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthpcurrentinputbuffername);
        dg_pusherror(pBHarrayhead, dg_evaluatebuffername);
        return;
    }

    u = *pbufferlength;

    // buffer is there because dg_getpbuffer worked so I can do this without checking
    pBH = &( ((Bufferhandle*)(pBHarrayhead->pbuf))[bufferid] );

    pbufferoffset = &(pBH->currentoffset); 

    *pbufferoffset = 0;

    while (*pbufferoffset < u)
    {
        //get off delimiters
        while(*pbufferoffset < u)
        {
            if (dg_isdelimiter(pbuffer[(*pbufferoffset)]))
            {
                (*pbufferoffset)++;
            }
            else
            {
                break;
            }
        }

        beginoffset = *pbufferoffset;
        pname = pbuffer + *pbufferoffset;

        // get on delimiter
        while(*pbufferoffset < u)
        {
            if (dg_isdelimiter(pbuffer[(*pbufferoffset)]))
            {
                break;
            }
            else
            {
                (*pbufferoffset)++;
            }
        }
        
        namelength = *pbufferoffset - beginoffset;
  
        // getting off delimiter after word. This is a forth standard requirement.
        if(*pbufferoffset < u)
        {
            (*pbufferoffset)++;
        } 

        if (namelength != 0)
        {
            // some routines need to know what the bufferid was (read only)
            //  need to set the current buffer every time because execute can call
            //  includefile or some other routine that will call this routine again (nested) 
            //  with a different buffer 
            olderrorcount = dg_geterrorcount(pBHarrayhead);

            dg_putbufferuint64(pBHarrayhead,
                DG_DATASPACE_BUFFERID,
                currentinterpretbuffer,
                bufferid);

            if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
            {
                dg_pusherror(pBHarrayhead, dg_forthpcurrentinputbuffername);
                dg_pusherror(pBHarrayhead, dg_evaluatebuffername);
                return;
            }

            // Standard says we have to try to look up definition before trying number conversion
            //  even though this can be really slow
            definition = dg_finddefinsearchorder(
                pBHarrayhead,
                pname,
                namelength);

            if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
            {
                dg_pusherror(pBHarrayhead, dg_evaluatebuffername);
                return; // may remove this return so the system can still try to execute the word if a vocabulary is broken
            }

            if (definition != DG_ENDOFWORDLIST)
            {
                dg_executedefinition(
                    pBHarrayhead,
                    definition);
                
                if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
                {
                    return;
                }
    
                dg_putbufferuint64(pBHarrayhead,
                    DG_DATASPACE_BUFFERID,
                    currentinterpretbuffer,
                    bufferid);

                if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
                {
                    dg_pusherror(pBHarrayhead, dg_forthpcurrentinputbuffername);
                    dg_pusherror(pBHarrayhead, dg_evaluatebuffername);
                    return;
                }            

                // what if the executed word frees the current input buffer???
                // then my pointer is invalid - may need to dg_getpbuffer every time through just in case, 
                // and make sure the buffer length didn't change. Could check it right here...
                pbuffer = dg_getpbuffer(
                    pBHarrayhead,
                    bufferid,
                    &pbufferlength);

                if (pbuffer == (unsigned char*)badbufferhandle)
                {
                    dg_pusherror(pBHarrayhead, dg_forthpcurrentinputbuffername);
                    dg_pusherror(pBHarrayhead, dg_evaluatebuffername);
                    return;
                }
                
                if (*pbufferlength != u)
                {
                    dg_pusherror(pBHarrayhead, dg_inputbufferlengthchangederror);
                    dg_pusherror(pBHarrayhead, dg_evaluatebuffername);
                    return;
                }
            }
            else
            {

                // this is a signed conversion, a - sign in front of the number is acceptable
                base = dg_getbufferuint64(
                    pBHarrayhead,
                    DG_DATASPACE_BUFFERID,
                    basevariable);

                if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
                {
                    dg_pusherror(pBHarrayhead, dg_forthbasename);
                    dg_pusherror(pBHarrayhead, dg_evaluatebuffername);
                    return;
                }

                number = dg_pchartonumber(
                    pname,
                    namelength,
                    base,
                    &flag); // this routine doesn't return errors

                if (flag != FORTH_FALSE)
                {
                    // we have a number, need to do the number
                    // push the number to the data stack
                    // if in compile mode, do literal
                    dg_pushbufferuint64(
                        pBHarrayhead,
                        DG_DATASTACK_BUFFERID,
                        number);

                    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
                    {
                        dg_pusherror(pBHarrayhead, dg_forthdatastackbufferidname);
                        dg_pusherror(pBHarrayhead, dg_evaluatebuffername);
                        return;
                    }    

                    pstate = (const char*)dg_getbufferuint64(
                        pBHarrayhead,
                        DG_DATASPACE_BUFFERID,
                        statevariable);

                    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
                    {    
                        dg_pusherror(pBHarrayhead, dg_forthstatename);
                        dg_pusherror(pBHarrayhead, dg_evaluatebuffername);
                        return;
                    }

                    if (pstate == dg_statecompile)
                    {
                        dg_forthliteral(pBHarrayhead);

                        if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
                        {    
                            dg_pusherror(pBHarrayhead, dg_evaluatebuffername);
                            return;
                        }
                    }
                }
                else 
                {
                    if (base == 10)
                    {
                        fnumber = dg_pchartof64 (
                            pname,        // pnumber,
                            namelength,   // length,
                            &flag);
                            
                        if (flag != FORTH_FALSE)
                        {
                            // we have a floating point number, need to do the number
                            // push the number to the data stack
                            // if in compile mode, do literal
                            dg_pushbufferuint64(
                                pBHarrayhead,
                                DG_F64STACK_BUFFERID,
                                *((UINT64*)(&fnumber))); // cast used to avoid conversion

                            if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
                            {
                                // dg_pusherror(pBHarrayhead, dg_forthdatastackbufferidname);
                                dg_pusherror(pBHarrayhead, dg_evaluatebuffername);
                                return;
                            }    

                            pstate = (const char*)dg_getbufferuint64(
                                pBHarrayhead,
                                DG_DATASPACE_BUFFERID,
                                statevariable);

                            if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
                            {    
                                dg_pusherror(pBHarrayhead, dg_forthstatename);
                                dg_pusherror(pBHarrayhead, dg_evaluatebuffername);
                                return;
                            }

                            if (pstate == dg_statecompile)
                            {
                                dg_forthfliteral(pBHarrayhead);  

                                if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
                                {    
                                    dg_pusherror(pBHarrayhead, dg_evaluatebuffername);
                                    return;
                                }
                            }
                        }
                        else
                        {
                            // base is 10 and word is not found
                            if (namelength > maxwordlength)
                            {
                                namelength = maxwordlength;
                            }

                            dg_putbuffersegment(
                                pBHarrayhead,
                                DG_DATASPACE_BUFFERID,
                                lastnotfoundword,
                                namelength,
                                pname);

                            if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
                            {    
                                dg_pusherror(pBHarrayhead, dg_evaluatebuffername);
                                return;
                            }

                            dg_putbufferbyte(
                                pBHarrayhead,
                                DG_DATASPACE_BUFFERID,
                                lastnotfoundword + namelength,
                                0);

                            if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
                            {    
                                dg_pusherror(pBHarrayhead, dg_evaluatebuffername);
                                return;
                            }

                            // word is not found - standard says we can do what we want in this case so...
                            //  I want the script to stop what it's doing and tell me which word wasn't found
                            //  Copying last word not found to a buffer as a 0 string and pushing pointer
                            //  to copy to error stack so it will show up on error stack.
                            dg_pusherror(
                                pBHarrayhead,
                                dg_evaluatebufferwordnotfounderror);
                            
                            return;
                        }
                    }
                    else
                    {
                        // base is not 10 and word is not found
                        if (namelength > maxwordlength)
                        {
                            namelength = maxwordlength;
                        }

                        dg_putbuffersegment(
                            pBHarrayhead,
                            DG_DATASPACE_BUFFERID,
                            lastnotfoundword,
                            namelength,
                            pname);

                        if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
                        {    
                            dg_pusherror(pBHarrayhead, dg_evaluatebuffername);
                            return;
                        }

                        dg_putbufferbyte(
                            pBHarrayhead,
                            DG_DATASPACE_BUFFERID,
                            lastnotfoundword + namelength,
                            0);

                        if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
                        {    
                            dg_pusherror(pBHarrayhead, dg_evaluatebuffername);
                            return;
                        }

                        // word is not found - standard says we can do what we want in this case so...
                        //  I want the script to stop what it's doing and tell me which word wasn't found
                        //  Copying last word not found to a buffer as a 0 string and pushing pointer
                        //  to copy to error stack so it will show up on error stack.
                        dg_pusherror(
                            pBHarrayhead,
                            dg_evaluatebufferwordnotfounderror);
                        
                        return;
                    }
                } 
            }
        }
    }
}


void dg_evaluatebuffer (
    Bufferhandle* pBHarrayhead,
    UINT64 bufferid)
{
    UINT64 oldinterpretbuffer;
    unsigned char* perrorline;
    UINT64 errorlinelength;
    UINT64 errorlinenumber = 0;
    
    unsigned char* pbuffer;
    UINT64* pbufferlength;
    
    const char* pError;
    
    UINT64 olderrorcount = dg_geterrorcount(pBHarrayhead);
    
    if (baderrorcount == olderrorcount)
    {
        return;
    }
    
    oldinterpretbuffer = dg_getbufferuint64(
        pBHarrayhead,
        DG_DATASPACE_BUFFERID,
        currentinterpretbuffer);
        
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthpcurrentinputbuffername);
        dg_pusherror(pBHarrayhead, dg_evaluatebuffername);
        return;
    }
       
    
    dg_putbufferuint64(
        pBHarrayhead,
        DG_DATASPACE_BUFFERID,
        currentinterpretbuffer,
        bufferid);

    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthpcurrentinputbuffername);
        dg_pusherror(pBHarrayhead, dg_evaluatebuffername);
        return;
    }
    
    
    dg_evaluatebuffersub(
        pBHarrayhead,
        bufferid);
        
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        if (0 == olderrorcount)
        {
            // seeing if the buffer was freed before I try to capture the error line 
            pError = dg_checkbuffer (
                pBHarrayhead,
                bufferid);
                    
            if (dg_success == pError)
            {
                // only capturing the line if one wasn't already captured
                //  since the last time the errors were cleared using EES
                if (0 == dg_getbufferlength (
                    pBHarrayhead,
                    DG_ERRORLINE_BUFFERID))
                {
                    perrorline = dg_noparseentirecurrentline(
                        pBHarrayhead,
                        &errorlinelength,
                        bufferid);
                            
                    dg_pushbuffersegment (
                        pBHarrayhead,
                        DG_ERRORLINE_BUFFERID,
                        errorlinelength,
                        perrorline);
                        
                    // not checking errors on purpose
                    
                    // current offset could be on character after line...
                    //  so I'm going to use the start of the captured error line
                    pbuffer = dg_getpbuffer(
                        pBHarrayhead,
                        bufferid,
                        &pbufferlength);
                    
                    if (perrorline > pbuffer)    
                    {
                        errorlinenumber = dg_noparselineatoffset(
                            pBHarrayhead,
                            bufferid,
                            perrorline - pbuffer);
                    }
                    
                    dg_putbufferuint64(
                        pBHarrayhead,
                        DG_DATASPACE_BUFFERID,
                        dg_errorlinenumber,
                        errorlinenumber);
                }
            }
        }
    }
    
    // putting old interpret buffer back on exit so SOURCE will work properly 4/23/2020
    
    // only want to capture error from dg_putbufferuint64....
    olderrorcount = dg_geterrorcount(pBHarrayhead);
    
    dg_putbufferuint64(
        pBHarrayhead,
        DG_DATASPACE_BUFFERID,
        currentinterpretbuffer,
        oldinterpretbuffer);

    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthpcurrentinputbuffername);
        dg_pusherror(pBHarrayhead, dg_evaluatebuffername);
        return;
    }
    
}


///////////////////////
// 
// dg_getevalpathtranslatedfileid
//
// returns
//    errors with badfilehandle, filename may be copied to filename buffer
//    no errors with badfilehandle - means no PATH_TRANSLATED filename
//    not badfilehandle, copies filename to filename buffer, and opens file
//
// I changed dg_argstoargsbuffer to copy PATH_TRANSLATED if there are no args
//  to the args buffer


const char* dg_getevalpathtranslatedfileidname = "dg_getevalpathtranslatedfileid";

UINT64 dg_getevalpathtranslatedfileid (Bufferhandle* pBHarrayhead)
{
    const char* perror;
    UINT64 fileid;
    unsigned char* pbuf;
    UINT64* pbuflength;
    UINT64 envvaluelength;

    UINT64 olderrorcount = dg_geterrorcount(pBHarrayhead);

    if (baderrorcount == olderrorcount)
    {
        return (badfilehandle);
    }

    perror = dg_getenvironmentvariable(
        pBHarrayhead,
        (const char*)"PATH_TRANSLATED", 
        (unsigned char*)badbufferhandle, 
        0, 
        &envvaluelength, 
        dg_success);

    if (perror != dg_success)
    {
        dg_pusherror(pBHarrayhead, perror);
        dg_pusherror(pBHarrayhead, dg_getenvironmentvariablename);
        dg_pusherror(pBHarrayhead, dg_getevalpathtranslatedfileidname);
        return (badfilehandle);
    }


    if (0 == envvaluelength)
    {
        return (badfilehandle);
    }

    dg_growbuffer(
        pBHarrayhead, 
        DG_SCRIPTFILENAME_BUFFERID, 
        envvaluelength, 
        &perror, 
        FORTH_FALSE);

    if (perror != dg_success)
    {
        dg_pusherror(pBHarrayhead, perror);
        dg_pusherror(pBHarrayhead, dg_growbuffername);
        dg_pusherror(pBHarrayhead, dg_getevalpathtranslatedfileidname);
        return (badfilehandle);
    }

    pbuf = dg_getpbuffer(
        pBHarrayhead,
        DG_SCRIPTFILENAME_BUFFERID,
        &pbuflength);

    if (pBHarrayhead->errorcount != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_getevalpathtranslatedfileidname);
        return (badfilehandle);
    }

    perror = dg_getenvironmentvariable(
            pBHarrayhead,
            (const char*)"PATH_TRANSLATED", 
            pbuf, 
            *pbuflength, 
            &envvaluelength, 
            dg_success);

    if (perror != dg_success)
    {
        dg_pusherror(pBHarrayhead, perror);
        dg_pusherror(pBHarrayhead, dg_getenvironmentvariablename);
        dg_pusherror(pBHarrayhead, dg_getevalpathtranslatedfileidname);
        return (badfilehandle);
    }

    dg_pushbufferbyte(
        pBHarrayhead,
        DG_SCRIPTFILENAME_BUFFERID,
        0);

    if (pBHarrayhead->errorcount != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_getevalpathtranslatedfileidname);
        return (badfilehandle);
    }

    pbuf = dg_getpbuffer(
        pBHarrayhead,
        DG_SCRIPTFILENAME_BUFFERID,
        &pbuflength);

    if (pBHarrayhead->errorcount != olderrorcount)
    {
        // could push error containing name of buffer here
        dg_pusherror(pBHarrayhead, dg_getevalpathtranslatedfileidname);
        return (badfilehandle);
    }

    perror = dg_openfileforread(
        (const char*)pbuf,
        &fileid,
        dg_success);

    if (perror != dg_success)
    {
        dg_pusherror(pBHarrayhead, perror);
        dg_pusherror(pBHarrayhead, dg_openfileforreadname);
        dg_pusherror(pBHarrayhead, dg_getevalpathtranslatedfileidname);
        return (badfilehandle);
    }

    return (fileid);
}




// if an args or path_translated file can not be found
//  and dglu is in cgi or isapi mode, try to run scriptnotfound.dglu
UINT64 dg_getscriptnotfoundfileid (Bufferhandle* pBHarrayhead)
{
    UINT64 fileid;
    const char* perror;

    UINT64 olderrorcount = dg_geterrorcount(pBHarrayhead);

    perror = dg_openfileforread(
        (const char*)"scriptnotfound.dglu",
        &fileid,
        dg_success);

    if (perror != dg_success)
    {
        dg_droptoerrorcount(
            pBHarrayhead,
            olderrorcount);
        
        return (badfilehandle);
    }

    return (fileid);
}





const char* dg_evaluatefileidname = "dg_evaluatefileid";

void dg_evaluatefileid (
    Bufferhandle* pBHarrayhead, 
    UINT64 fileid, 
    UINT64* pfirsttimethrough)
{
    const char* flag;
    const char* filetype;
    UINT64 length;
    UINT64 bufferid;
    unsigned char* pbuf;
    UINT64* pbuflength;
    UINT64 numread;
    UINT64 myexitmainflag;
    UINT64 myeof;
    UINT64 isglulistflag;
    UINT64 hlistid;
    const char* pError;
    
    unsigned char* perrorline;
    UINT64 errorlinelength;

    UINT64 olderrorcount = dg_geterrorcount(pBHarrayhead);

    if (baderrorcount == olderrorcount)
    {
        return;
    }

    flag = dg_getfiletype(
        pBHarrayhead,
        fileid, 
        &filetype, 
        dg_success);

    if (flag != dg_success)
    {
        dg_pusherror(pBHarrayhead, flag);
        dg_pusherror(pBHarrayhead, dg_getfiletypename);
        dg_pusherror(pBHarrayhead, dg_evaluatefileidname);
        return;
    }

    if (filetype == dg_filetypeunknown)
    {
        dg_pusherror(pBHarrayhead, dg_filetypeunknownerror);
        dg_pusherror(pBHarrayhead, dg_evaluatefileidname);
        return;
    }

    if (filetype == dg_filetypedisk)
    {
        if (FORTH_FALSE == *pfirsttimethrough)
        {
            // someone put a QUIT, ABORT, or ABORT" in a script file
            return;
        }

        flag = dg_getfilelength(
            pBHarrayhead,
            fileid, 
            &length, 
            dg_success);

        if (flag != dg_success)
        {
            dg_pusherror(pBHarrayhead, flag);
            dg_pusherror(pBHarrayhead, dg_getfilelengthname);
            dg_pusherror(pBHarrayhead, dg_evaluatefileidname);
            return;
        }

        // allocate buffer large enough to hold file data
        bufferid = dg_newbuffer(
            pBHarrayhead, 
            length, 
            length, 
            &flag, 
            FORTH_FALSE);

        if (flag != dg_success)
        {
            dg_pusherror(pBHarrayhead, flag);
            dg_pusherror(pBHarrayhead, dg_newbuffername);
            dg_pusherror(pBHarrayhead, dg_evaluatefileidname);
            return;
        }

        dg_growbuffer(
            pBHarrayhead,
            bufferid,
            length,
            &flag,
            FORTH_FALSE);

        if (flag != dg_success)
        {
            dg_pusherror(pBHarrayhead, flag);
            dg_pusherror(pBHarrayhead, dg_growbuffername);
            dg_pusherror(pBHarrayhead, dg_evaluatefileidname);
            return;
        }
        
        pbuf = dg_getpbuffer(
            pBHarrayhead,
            bufferid,
            &pbuflength);

        if (pBHarrayhead->errorcount != olderrorcount)
        {
            dg_pusherror(pBHarrayhead, dg_evaluatefileidname);
            return;
        }

        flag = dg_readfile(
            pBHarrayhead,
            fileid, 
            pbuf, 
            length, 
            0, 
            &numread, 
            dg_success); 

        if (flag != dg_success)
        {
            dg_freebuffer(pBHarrayhead, bufferid);
            dg_pusherror(pBHarrayhead, flag);
            dg_pusherror(pBHarrayhead, dg_readfilename);
            dg_pusherror(pBHarrayhead, dg_evaluatefileidname);
            return;
        }

        // This should never happen. If OS says it's availabe we should get it, but it DOES happen occassionally on win32.
        if (numread != length)
        {
            // os did not return entire file
            // could try a second read here...
            dg_freebuffer(pBHarrayhead, bufferid);
            dg_pusherror(pBHarrayhead, dg_osdidlessthanavailableerror);  
            dg_pusherror(pBHarrayhead, dg_readfilename);
            dg_pusherror(pBHarrayhead, dg_evaluatefileidname);
            return;
        }

        *pfirsttimethrough = FORTH_FALSE;
        
        // check to see if file is a glu/nglu list
        //  check for packed lstring... if so, assume it's a packed hlist
        //  if so, unpack the hlist then glu/nglu it...
        isglulistflag = dg_isbufferapackedlstring (
            pBHarrayhead,
            bufferid);
        
        if (pBHarrayhead->errorcount != olderrorcount)
        {
            dg_pusherror(pBHarrayhead, dg_evaluatefileidname);
            return;
        }
        
        if (FORTH_FALSE != isglulistflag)
        {
            hlistid = dg_unpackhlist (
                pBHarrayhead,
                bufferid);
            
            if (pBHarrayhead->errorcount != olderrorcount)
            {
                dg_pusherror(pBHarrayhead, dg_evaluatefileidname);
                return;
            }
        
            dg_glu(
                pBHarrayhead,
                hlistid);
            
            if (pBHarrayhead->errorcount != olderrorcount)
            {
                dg_pusherror(pBHarrayhead, dg_evaluatefileidname);
                return;
            }
            
            return;
        }

        // otherwise assume it is a script file
        dg_evaluatebuffer(
            pBHarrayhead,
            bufferid);
        
        dg_freebuffer(
            pBHarrayhead,
            bufferid);

        return;
    }

   ////////////////////////////////////////////
   // going to treat console and pipe the same
   // error output will go to stdout
   // and prompts will be on

    dg_forthdoprompt(pBHarrayhead);

    myexitmainflag = dg_getbufferuint64(
        pBHarrayhead,
        DG_DATASPACE_BUFFERID, 
        exitmainflag);
        

    while(myexitmainflag == FORTH_FALSE)
    {
        olderrorcount = dg_geterrorcount(pBHarrayhead);

        myeof = dg_getline(
            pBHarrayhead, 
            fileid,
            DG_TERMINALINPUT_BUFFERID, 
            dg_success);

        if (pBHarrayhead->errorcount != olderrorcount)
        {
            dg_pusherror(pBHarrayhead, dg_evaluatefileidname);
            return;
        }
        else
        {
            *pfirsttimethrough = FORTH_FALSE;

            dg_evaluatebuffer(
                pBHarrayhead,
                DG_TERMINALINPUT_BUFFERID);

            // dg_forthdoterrors(pBHarrayhead);

            myexitmainflag = dg_getbufferuint64(
                pBHarrayhead, 
                DG_DATASPACE_BUFFERID,
                exitmainflag);

            dg_forthcr(pBHarrayhead); 

            if (myexitmainflag == FORTH_FALSE)
            {
                dg_forthdoprompt(pBHarrayhead);
            } 
        }
    }
}



void dg_sendnoscriptfilepage (Bufferhandle* pBHarrayhead)
{
    dg_printzerostring(pBHarrayhead,  (unsigned char*)"Content-type: text/html\r\n\r\n");
    dg_printzerostring(pBHarrayhead,  (unsigned char*)"<html><head></head><body>\r\n");
    dg_printzerostring(pBHarrayhead,  (unsigned char*)"<h1 align=center>No script file specified and default noscript.dglu script not found.</h1>\r\n");
    dg_printzerostring(pBHarrayhead,  (unsigned char*)"<p>You need to specify a script file.</p>");
    dg_printzerostring(pBHarrayhead,  (unsigned char*)"<p>For example:</p>");
    dg_printzerostring(pBHarrayhead,  (unsigned char*)"<p>http://www.whereeverthisis.com/cgi-bin/diaperglu?scriptfilename.dglu</p>");
    dg_printzerostring(pBHarrayhead,  (unsigned char*)"<p>or http://www.whereeverthisis.com/diaperglu.exe?scriptfilename.dglu</p>");
    dg_printzerostring(pBHarrayhead,  (unsigned char*)"<p>or just http://www.whereeverthisis.com/cgi-bin/scriptfilename.dglu</p>");
    dg_printzerostring(pBHarrayhead,  (unsigned char*)"</body></html>\r\n");
}


void dg_sendfilenotfoundpage (
    Bufferhandle* pBHarrayhead,
    UINT64 olderrorcount,
    UINT64 fileid)
{
    unsigned char* pbuf;
    UINT64* pbuflength;
    const char* perror;
    UINT64 envvaluelength;

    pbuf = dg_getpbuffer(
        pBHarrayhead,
        DG_SCRIPTFILENAME_BUFFERID,
        &pbuflength);

    perror = dg_getenvironmentvariable(
        pBHarrayhead,
        (const char*)"SERVER_NAME", 
        (unsigned char*)badbufferhandle, 
        0, 
        &envvaluelength, 
        dg_success);

    if ((0 == envvaluelength) ||
        ((UINT64)largestunsignedint == envvaluelength))
    {
        // not a cgi script 
        dg_printzerostring(pBHarrayhead, (unsigned char*)"\r\nCould not load script file ");
        dg_writestdout(pBHarrayhead, pbuf, *pbuflength);
        dg_printzerostring(pBHarrayhead, (unsigned char*)"\r\nGot error ");
        perror = dg_geterror(pBHarrayhead, olderrorcount);
        dg_printzerostring(pBHarrayhead, (unsigned char*)perror);
        dg_printzerostring(pBHarrayhead, (unsigned char*)"\r\n\r\n");
        return;
    }

    dg_printzerostring(pBHarrayhead, (unsigned char*)"Content-type: text/html\r\n\r\n");
    dg_printzerostring(pBHarrayhead, (unsigned char*)"<html><head></head><body>\r\n");
    dg_printzerostring(pBHarrayhead, (unsigned char*)"<h3 align=center>Could not load script file ");
    dg_writestdout(pBHarrayhead, pbuf, *pbuflength);
    dg_printzerostring(pBHarrayhead, (unsigned char*)"</h3>\r\n");
    dg_printzerostring(pBHarrayhead, (unsigned char*)"<br><h3 align=center>Got error ");
    perror = dg_geterror(pBHarrayhead, olderrorcount);
    dg_printzerostring(pBHarrayhead, (unsigned char*)perror);
    dg_printzerostring(pBHarrayhead, (unsigned char*)"</h3>\r\n");
    dg_showinputmode(pBHarrayhead, fileid);
    dg_printzerostring(pBHarrayhead, (unsigned char*)"</body></html>\r\n");
}


const char* dg_showinputmodename = "dg_showinputmode";

void dg_showinputmode (
    Bufferhandle* pBHarrayhead,
    UINT64 fileid)
{
    unsigned char* pbuf;
    UINT64* pbuflength;
    const char* filetype = dg_filetypeunknown;
    const char* pError;

    UINT64 mybufid = (UINT64)badbufferhandle;

    // ignoring errors in this routine, except not being able to allocate the buffer
    
    mybufid = dg_newbuffer(
        pBHarrayhead,
        0x1000,
        0x1000,
        &pError,
        FORTH_FALSE);

    if (pError != dg_success)
    {
        dg_pusherror(pBHarrayhead, pError);
        dg_pusherror(pBHarrayhead, dg_newbuffername);
        dg_pusherror(pBHarrayhead, dg_showinputmodename);
        return;
    }

    dg_printzerostring(pBHarrayhead, (unsigned char*)"<PRE>\r\n");
    
    pbuf = dg_getpbuffer(
        pBHarrayhead,
        DG_SCRIPTFILENAME_BUFFERID,
        &pbuflength);
    
    dg_printzerostring(pBHarrayhead, (unsigned char*)"\r\ncalculated script file name = ");
    dg_writestdout(
        pBHarrayhead,
        pbuf,
        *pbuflength);

    dg_printzerostring(pBHarrayhead, (unsigned char*)"  length = ");
    dg_writestdoutuinttodec(
        pBHarrayhead,
        *pbuflength);

    if (*pbuflength > 0)
    {
        dg_printzerostring(pBHarrayhead, (unsigned char*)", last character = ");
        dg_writestdoutuinttodec(
            pBHarrayhead,
            pbuf[*pbuflength - 1]);
    }

    pbuf = dg_getpbuffer(
        pBHarrayhead,
        DG_ARGS_BUFFERID,
        &pbuflength);
    
    dg_printzerostring(pBHarrayhead, (unsigned char*)"\r\nargs buffer = ");
    dg_writestdout(
        pBHarrayhead,
        pbuf,
        *pbuflength);

    if (fileid != badfilehandle)
    {
        dg_getfiletype(
            pBHarrayhead,
            fileid,
            &filetype,
            dg_success);
    }

    dg_printzerostring(pBHarrayhead, (unsigned char*)"\r\nfiletype = ");
    dg_printzerostring(pBHarrayhead, (unsigned char*)filetype);

    dg_printzerostring(pBHarrayhead, (unsigned char*)"\r\n");
    
    
    ////////////////////////////////////

    dg_clearbuffer(
        pBHarrayhead,
        mybufid);

    dg_pushenvtobuf (
        pBHarrayhead,
        mybufid,
        (const char*)"SERVER_SOFTWARE");

    pbuf = dg_getpbuffer(pBHarrayhead, mybufid, &pbuflength);

    dg_printzerostring(pBHarrayhead, (unsigned char*)"\r\nSERVER_SOFTWARE = ");
    dg_writestdout(
        pBHarrayhead,
        pbuf,
        *pbuflength);

    dg_printzerostring(pBHarrayhead, (unsigned char*)"\r\n");

    ////////////////////////////////////

    dg_clearbuffer(
        pBHarrayhead,
        mybufid);

    dg_pushenvtobuf (
        pBHarrayhead,
        mybufid,
        (const char*)"SERVER_NAME");

    pbuf = dg_getpbuffer(
        pBHarrayhead,
        mybufid,
        &pbuflength);

    dg_printzerostring(pBHarrayhead, (unsigned char*)"\r\nSERVER_NAME = ");
    
    dg_writestdout(
        pBHarrayhead,
        pbuf,
        *pbuflength);

    dg_printzerostring(pBHarrayhead, (unsigned char*)"\r\n");

    ////////////////////////////////////

    dg_clearbuffer(pBHarrayhead, mybufid);

    dg_pushenvtobuf (
        pBHarrayhead,
        mybufid,
        (const char*)"SCRIPT_FILENAME");

    pbuf = dg_getpbuffer(
        pBHarrayhead,
        mybufid,
        &pbuflength);

    dg_printzerostring(pBHarrayhead, (unsigned char*)"\r\nSCRIPT_FILENAME = ");
    
    dg_writestdout(
        pBHarrayhead,
        pbuf,
        *pbuflength);

    dg_printzerostring(pBHarrayhead, (unsigned char*)"\r\n");

    ////////////////////////////////

    dg_clearbuffer(pBHarrayhead, mybufid);

    dg_pushenvtobuf (
        pBHarrayhead,
        mybufid,
        (const char*)"SCRIPT_NAME");

    pbuf = dg_getpbuffer(
        pBHarrayhead,
        mybufid,
        &pbuflength);

    dg_printzerostring(pBHarrayhead, (unsigned char*)"\r\nSCRIPT_NAME = ");
    dg_writestdout(
        pBHarrayhead,
        pbuf,
        *pbuflength);

    dg_printzerostring(pBHarrayhead, (unsigned char*)"\r\n");

    ////////////////////////////////

    dg_clearbuffer(pBHarrayhead, mybufid);

    dg_pushenvtobuf (
        pBHarrayhead,
        mybufid,
        (const char*)"SCRIPT_TRANSLATED");

    pbuf = dg_getpbuffer(
        pBHarrayhead,
        mybufid,
        &pbuflength);

    dg_printzerostring(pBHarrayhead, (unsigned char*)"\r\nSCRIPT_TRANSLATED = ");
    dg_writestdout(
        pBHarrayhead,
        pbuf,
        *pbuflength);

    dg_printzerostring(pBHarrayhead, (unsigned char*)"\r\n");

    ////////////////////////////////////////////

    dg_clearbuffer(pBHarrayhead, mybufid);

    dg_pushenvtobuf (
        pBHarrayhead,
        mybufid,
        (const char*)"PATH_INFO");

    pbuf = dg_getpbuffer(
        pBHarrayhead,
        mybufid,
        &pbuflength);

    dg_printzerostring(pBHarrayhead, (unsigned char*)"\r\nPATH_INFO = ");
    dg_writestdout(
        pBHarrayhead,
        pbuf,
        *pbuflength);


    dg_printzerostring(pBHarrayhead, (unsigned char*)"\r\n");

    /////////////////////////////////////////////////////

    dg_clearbuffer(pBHarrayhead, mybufid);

    dg_pushenvtobuf (
        pBHarrayhead,
        mybufid,
        (const char*)"PATH_TRANSLATED");

    pbuf = dg_getpbuffer(pBHarrayhead, mybufid, &pbuflength);

    dg_printzerostring(pBHarrayhead, (unsigned char*)"\r\nPATH_TRANSLATED = ");
    dg_writestdout(
        pBHarrayhead,
        pbuf,
        *pbuflength);


    dg_printzerostring(pBHarrayhead, (unsigned char*)"\r\n");

    ////////////////////////////////////

    dg_clearbuffer(
        pBHarrayhead,
        mybufid);

    dg_pushenvtobuf (
        pBHarrayhead,
        mybufid,
        (const char*)"DOCUMENT_ROOT");

    pbuf = dg_getpbuffer(
        pBHarrayhead,
        mybufid,
        &pbuflength);

    dg_printzerostring(pBHarrayhead, (unsigned char*)"\r\nDOCUMENT_ROOT = ");
    dg_writestdout(
        pBHarrayhead,
        pbuf,
        *pbuflength);

    dg_printzerostring(pBHarrayhead, (unsigned char*)"\r\n");

    ////////////////////////////////////

    dg_clearbuffer(pBHarrayhead, mybufid);

    dg_pushenvtobuf (
        pBHarrayhead,
        mybufid,
        (const char*)"QUERY_STRING");

    pbuf = dg_getpbuffer(pBHarrayhead, mybufid, &pbuflength);

    dg_printzerostring(pBHarrayhead, (unsigned char*)"\r\nQUERY_STRING = ");
    dg_writestdout(
        pBHarrayhead,
        pbuf,
        *pbuflength);

    dg_printzerostring(pBHarrayhead, (unsigned char*)"\r\n");

    ////////////////////////////////////////

    dg_forthdoterrors(pBHarrayhead);
    dg_printzerostring(pBHarrayhead, (unsigned char*)"</PRE>\r\n");

    dg_printzerostring(pBHarrayhead, (unsigned char*)"</body></html>\r\n"); 

    dg_freebuffer(
        pBHarrayhead,
        mybufid);
}


void dg_showerrorspage (Bufferhandle* pBHarrayhead)
{
    const char* perror;
    UINT64 envvaluelength;
    
    UINT64 olderrorcount = dg_geterrorcount(pBHarrayhead);

    if (0 == olderrorcount)
    {
        return;
    }

    if (baderrorcount == olderrorcount)
    {
        // pBHarrayhead is broken so no error stack
        //  and program shouldn't have gotten to here
        return;
    }

    if (FORTH_FALSE == dg_getbufferuint64(
        pBHarrayhead,
        DG_DATASPACE_BUFFERID,
        showerrorsonexitflag))
    {
        return;
    }

    perror = dg_getenvironmentvariable(
        pBHarrayhead,
        (const char*)"SERVER_NAME", 
        (unsigned char*)badbufferhandle, 
        0, 
        &envvaluelength, 
        dg_success);

    if ((0 == envvaluelength) ||
        ((UINT64)largestunsignedint == envvaluelength))
    {
        // not a cgi script 
        dg_printzerostring(pBHarrayhead, (unsigned char*)"\r\nErrors:\r\n");
        dg_forthdoterrors(pBHarrayhead);
        dg_printzerostring(pBHarrayhead, (unsigned char*)"\r\n\r\n");
        dg_printzerostring(pBHarrayhead, (unsigned char*)"The line that probably caused the errors:\r\n");
        dg_forthdoterrorline(pBHarrayhead);
        dg_printzerostring(pBHarrayhead, (unsigned char*)"\r\n\r\n");

        //dg_printzerostring(pBHarrayhead, (unsigned char*)"<br>Last name created: ");
        //dg_forthlatest(pBHarrayhead);
        //dg_forthtooname(pBHarrayhead);
        //dg_forthgetpbufferoffset(pBHarrayhead);
        //dg_forthtype0string(pBHarrayhead);
        //dg_printzerostring(pBHarrayhead, (unsigned char*)"\r\n");
        return;
    }

    dg_printzerostring(pBHarrayhead, (unsigned char*)"Content-type: text/html\r\n\r\n");
    dg_printzerostring(pBHarrayhead, (unsigned char*)"<html><head></head><body>\r\n");
 
    dg_printzerostring(pBHarrayhead, (unsigned char*)"<h3>Errors:</h3><br>\r\n");
    dg_printzerostring(pBHarrayhead, (unsigned char*)"<PRE>\r\n");
    dg_forthdoterrors(pBHarrayhead);
    dg_printzerostring(pBHarrayhead, (unsigned char*)"</PRE>\r\n");

    //dg_printzerostring(pBHarrayhead, (unsigned char*)"<br>Last name created: ");
    //dg_forthlatest(pBHarrayhead);
    //dg_forthtooname(pBHarrayhead);
    //dg_forthgetpbufferoffset(pBHarrayhead);
    //dg_forthtype0string(pBHarrayhead);
    //dg_printzerostring(pBHarrayhead, (unsigned char*)"\r\n");

    dg_printzerostring(pBHarrayhead, (unsigned char*)"</body></html>\r\n"); 
}

void dg_showinputmodepage (Bufferhandle* pBHarrayhead, UINT64 fileid)
{
    dg_printzerostring(pBHarrayhead, (unsigned char*)"Content-type: text/html\r\n\r\n");
    dg_printzerostring(pBHarrayhead, (unsigned char*)"<html><head></head><body>\r\n");
    
    dg_showinputmode(pBHarrayhead, fileid);
}

void dg_sendgetenvvarerrorpage (Bufferhandle* pBHarrayhead)
{
    UINT64 olderrorcount = dg_geterrorcount(pBHarrayhead);

    if (baderrorcount == olderrorcount)
    {
        // pBHarrayhead is broken so no error stack
        //  and program shouldn't have gotten to here
        return;
    }

    dg_printzerostring(pBHarrayhead, (unsigned char*)"Content-type: text/html\r\n\r\n");
    dg_printzerostring(pBHarrayhead, (unsigned char*)"<html><head></head><body>\r\n");
 
    dg_printzerostring(pBHarrayhead, (unsigned char*)"<h3>Error</h3><br>\r\n");
    dg_printzerostring(
        pBHarrayhead, 
        (unsigned char*)"Got an error trying to retrieve an environment variable from the server.\r\n");

    // for version 3.1 June 27, 2013 J.N.
    //   FreeBSD and Linux, Diaperglu gets the environment variables from the argv array passed in.
    //   Mac OS X, Diaperglu calls operationg system GetEnv function
    //   win32 ISAPI, Diaperglu calls GetServerVariable in extension control block
    //   win32 not ISAPI, Diaperglu call GetEnvironmentVariable

    dg_printzerostring(pBHarrayhead, (unsigned char*)"<p><PRE>\r\n");
    dg_forthdoterrors(pBHarrayhead);
    dg_printzerostring(pBHarrayhead, (unsigned char*)"</PRE></p>\r\n");

    dg_printzerostring(pBHarrayhead, (unsigned char*)"</body></html>\r\n"); 
}


// file mode
//   just diaperglu on command line (no args)
//     do command line mode
//   diaperglu and script filename on command line - scriptfile exists
//     evaluate scriptfile
//   diaperglu and script filename on command line - scriptfile not found
//     if noscript.dglu exists, evaluate noscript.dglu
//     if noscript.dglu does not exists, send error to stdout that 
//       could not open scriptfile
//
//   in file mode:
//     SERVER_NAME will not exist ( or be empty? )
//     also isapi handle in pBHarrayhead will not be set

// cgi mode for IIS7
//   just .../diaperglu (cgi) specified in url
//     args buffer has: "C:\inetpub\wwwroot"
//     SCRIPT_FILENAME has: nothing
//     PATH_INFO has: ""
//     PATH_TRANSLATED has: "C:\inetpub\wwwroot"
//     QUERY_STRING has: nothing
//
//   .../diaperglu?scriptfilename (cgi) specified in url
//     args buffer has "helloworld.dglu"
//     SCRIPT_FILENAME has: nothing
//     PATH_INFO has:  ""
//     PATH_TRANSLATED has: "C:\inetpub\wwwroot"
//     QUERY_STRING has: "helloworld.dglu"
//
//   .../scriptfilename (cgi) specified in url
//     args buffer has: "C:\inetpub\wwwroot\helloworld.dglu"
//     SCRIPT_FILENAME has: nothing
//     PATH_INFO has: "/helloworld.dglu"  (OHH! IIS is inserting dll name into path)
//     PATH_TRANSLATED has: "C:\inetpub\wwwroot\helloworld.dglu"
//     QUERY_STRING has: nothing
//
//   in cgi mode
//     SERVER_NAME will exist and not be 0 length
//     no isapi handle in pBHarrayhead

// cgi mode for IIS10

//     args buffer has: nothing
//     SCRIPT_FILENAME has: nothing
//     SCRIPT_NAME has: "/cgi-bin/diaperglu.exe"
//     PATH_INFO has: ""
//     PATH_TRANSLATED has: "C:\inetpub\wwwroot"
//     QUERY_STRING has: nothing
//
//   .../diaperglu?scriptfilename (cgi) specified in url
//     args buffer has "helloworld.dglu"
//     SCRIPT_FILENAME has: "C:\inetpub\wwwroot\helloworld.dglu"
//     SCRIPT_NAME has: "/cgi-bin/diaperglu.exe"
//     SCRIPT_TRANSLATED has: nothing
//     PATH_INFO has:  ""
//     PATH_TRANSLATED has: "C:\inetpub\wwwroot"
//     DOCUMENT_ROOT has: nothing
//     QUERY_STRING has: "helloworld.dglu"
//
//   .../scriptfilename (cgi) specified in url 
//     args buffer has: nothing
//     SCRIPT_FILENAME has: nothing
//     SCRIPT_NAME has "/cgi-bin/helloworld.dglu "
//     SCRIPT_TRANSLATED has" nothing
//     PATH_INFO has: "/cgi-bin/helloworld.dglu"  
//     PATH_TRANSLATED has: "C:\inetpub\wwwroot\mycgibin\helloworld.dglu"
//     DOCUMENT_ROOT has: nothing
//     QUERY_STRING has: nothing
//
//   in cgi mode
//     SERVER_NAME will exist and not be 0 length
//     no isapi handle in pBHarrayhead

// isapi mode for IIS 7
//    just .../diaperglu (isapi) specified in url
//     args buffer (should be PATH_TRANSLATED) has: "C:\inetpub\wwwroot"
//     SCRIPT_FILENAME has: nothing
//     PATH_INFO has: ""
//     PATH_TRANSLATED has: "C:\inetpub\wwwroot"
//     QUERY_STRING has: nothing
//     SCRIPT_NAME has: "/diaperglu.dll"
//
//    .../diaperglu?scriptfilename (isapi) specified in url
//     args buffer (should be PATH_TRANSLATED) has: "C:\inetpub\wwwroot"
//     SCRIPT_FILENAME has: nothing
//     PATH_INFO has: ""
//     PATH_TRANSLATED has: "C:\inetpub\wwwroot"
//     QUERY_STRING has: "helloworld.asdglu"
//     SCRIPT_NAME has: "/diaperglu.dll"
//
//    .../scriptfilename (isapi) specified in url
//     args buffer (should be PATH_TRANSLATED) has: C:\inetpub\wwwroot\helloworld.asdglu"
//     SCRIPT_FILENAME has: nothing
//     PATH_INFO has: "/helloworld.asdglu" (OHH! IIS is inserting dll name into path)
//     PATH_TRANSLATED has: "C:\inetpub\wwwroot\helloworld.asdglu"
//     QUERY_STRING has: nothing
//     SCRIPT_NAME has: "/helloworld.asdglu"
//
//    in isapi mode
//      SERVER_NAME will exist and not be 0 length
//      isapi handle in pBHarrayhead


// for both isapi and cgi for IIS7, if both query string and path info are empty,
//  then the user invoked just diaperglu without specifying a script file

//  after this for cgi, args buffer has the script filename to do

//  after this for isapi, if PATH_INFO is empty, then the query string should
//   have the script file to execute, (may have to append it to PATH_TRANSLATED)
//                       if PATH_INFO is not empty, then PATH_TRANSLATED (args buffer)
//   has the script file to execute


// cgi mode for Apache on Mac OS X 10.8.2
//   if args buffer is empty the user invoked Diaperglu
//   if args buffer after last / matches SCRIPT_NAME after last / the user invoked
//    scriptname.dglu 
//   if args buffer after last / does NOT match SCRIPT_NAME after last / the user
//    invoked diaperglu?scriptname.dglu. Would like to pull out just the first
//    parameter's value. (Window's mode already supports this.)

// For both Apache2 and IIS7, if SCRIPT_NAME after last slash matches
//  args buffer after last slash then the user entered scriptname.dglu
//  and the args buffer holds the correct script filename to run

// For both Apache2 and IIS7, if SCRIPT_NAME after last slash does NOT match
//  args buffer after last slash, AND QUERY_STRING is empty then no script
//  file was specified. (User invoked Diaperglu directly)

// For both Apache2 and IIS7, if SCRIPT_NAME after last slash does NOT match
//  args buffer after last slash, AND QUERY_STRING is not empty then 
//  use the first parameter's value as the script file name. 
//  Note: IIS7 requires the full path to the script file name so if the 
//   first parameter's value on IIS7 does NOT have a : in it, assume it is a 
//   partial path and that SCRIPT_TRANSLATED has the root path.
//  Note: Apache seems to accept partial paths so just use the first parameter's
//   value as the script file name. If you want to make a full path you could
//   get the base path from DOCUMENT_ROOT, but this is probably not required. 

const char* dg_doinputstuffname = "dg_doinputstuff";

void dg_doinputstuff (
    Bufferhandle* pBHarrayhead,
    UINT64* pfirsttimethrough)
{
    UINT64 fileid = badfilehandle;

    UINT64 olderrorcount = dg_geterrorcount(pBHarrayhead);

    if (baderrorcount == olderrorcount)
    {
        return;
    }

    dg_clearbuffer(
        pBHarrayhead,
        DG_SCRIPTNAME_BUFFERID);

    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        return;
    }

    dg_pushenvtobuf (
        pBHarrayhead,
        DG_SCRIPTNAME_BUFFERID,
        (const char*)"SCRIPT_NAME");

    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_doinputstuffname);
        dg_pusherror(pBHarrayhead, (const char*)"SCRIPT_NAME");
        dg_sendgetenvvarerrorpage(pBHarrayhead);
        dg_clearerrors(pBHarrayhead);
        return;
    }

    dg_clearbuffer(
        pBHarrayhead,
        DG_QUERYSTRING_BUFFERID);

    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        return;
    }

    dg_pushenvtobuf (
        pBHarrayhead,
        DG_QUERYSTRING_BUFFERID,
        (const char*)"QUERY_STRING");

    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_doinputstuffname);
        dg_pusherror(pBHarrayhead, (const char*)"QUERY_STRING");
        dg_sendgetenvvarerrorpage(pBHarrayhead);
        dg_clearerrors(pBHarrayhead);
        return;
    }

    dg_clearbuffer(
        pBHarrayhead,
        DG_SERVERNAME_BUFFERID);

    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        return;
    }

    dg_pushenvtobuf (
        pBHarrayhead,
        DG_SERVERNAME_BUFFERID,
        (const char*)"SERVER_NAME");

    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_doinputstuffname);
        dg_pusherror(pBHarrayhead, (const char*)"SERVER_NAME");
        dg_sendgetenvvarerrorpage(pBHarrayhead);
        dg_clearerrors(pBHarrayhead);
        return;
    }

     dg_clearbuffer(
        pBHarrayhead,
        DG_SERVERSOFTWARE_BUFFERID);

    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        return;
    }

    dg_pushenvtobuf (
        pBHarrayhead,
        DG_SERVERSOFTWARE_BUFFERID,
        (const char*)"SERVER_SOFTWARE");

    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_doinputstuffname);
        dg_pusherror(pBHarrayhead, (const char*)"SERVER_SOFTWARE");
        dg_sendgetenvvarerrorpage(pBHarrayhead);
        dg_clearerrors(pBHarrayhead);
        return;
    }

    // dg_openfileforwritenew((const char*)"c:\\dglu\\gothere2.txt", &hfile, dg_success);
    // dg_writefile(pBHarrayhead, hfile, (unsigned char*)"got here too", 13, dg_success);
    // dg_writefileuint64todec(pBHarrayhead, hfile, errorcode);
    // dg_closefile(hfile, dg_success);

    fileid = dg_getevaluatefileid(pBHarrayhead);

    // dg_showinputmodepage(pBHarrayhead, fileid);

    if (pBHarrayhead->errorcount != olderrorcount)
    {
        // may want to parse actual errors here
        dg_sendfilenotfoundpage(
            pBHarrayhead,
            olderrorcount,
            fileid);
            
        dg_clearerrors(pBHarrayhead);
        return;
    }

    if (dg_stdinbadfilehandle == fileid)
    {
        dg_printzerostring(pBHarrayhead, (unsigned char*)"\nAs unbelievable as it might seem, Diaperglu could not open stdin\n");
        return;
    }

    if (badfilehandle == fileid)
    {
        dg_sendnoscriptfilepage(pBHarrayhead);
        return;
    }

    dg_querygetpost(
        pBHarrayhead,
        *pfirsttimethrough);

    dg_evaluatefileid(
        pBHarrayhead,
        fileid,
        pfirsttimethrough);

    // even if we get errors still going to close
    //  and errors may have been from script file or user input
    dg_closeevalfileid(
        pBHarrayhead,
        fileid);

    dg_showerrorspage(pBHarrayhead);
}

UINT64 dg_functiontable[] = {
    (UINT64)&dg_pushdatastack,
    (UINT64)&dg_forthdup
};

const char dg_loadfilename[] = "dg_loadfile";

UINT64 dg_loadfile (
    Bufferhandle* pBHarrayhead,
    unsigned char* pfilename,
    UINT64 filenamelength)
{
    UINT64 mybufferid;
    
    UINT64 olderrorcount = dg_geterrorcount(pBHarrayhead);

    if (baderrorcount == olderrorcount)
    {
        return(dg_badbufferid);
    }
    
    // push file name to string stack
    //  the string stack is used because a null must be appended to the file name
    dg_pushlstring (
        pBHarrayhead,
        DG_STRINGOFFSETSTACK_BUFFERID,
        DG_STRINGSTRINGSTACK_BUFFERID,
        filenamelength,
        pfilename);
    
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_loadfilename);
        return(dg_badbufferid);
    }
    
    // dg_forthloadfilestring
    dg_forthloadfilestring(pBHarrayhead);
    
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_loadfilename);
        return(dg_badbufferid);
    }
    
    // pop the buffer id
    mybufferid = dg_popbufferuint64(
        pBHarrayhead,
        DG_DATASTACK_BUFFERID);
    
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_loadfilename);
        return(dg_badbufferid);
    }
    
    // return the buffer id
    return(mybufferid);
}


const char dg_nglufilename[] = "dg_nglufile";

void dg_nglufile (
    Bufferhandle* pBHarrayhead,
    unsigned char* pfilename,
    UINT64 filenamelength)
{
    UINT64 mybufferid;
    
    UINT64 olderrorcount = dg_geterrorcount(pBHarrayhead);

    if (baderrorcount == olderrorcount)
    {
        return;
    }
    
    // push file name to string stack
    //  the string stack is used because a null must be appended to the file name
    dg_pushlstring (
        pBHarrayhead,
        DG_STRINGOFFSETSTACK_BUFFERID,
        DG_STRINGSTRINGSTACK_BUFFERID,
        filenamelength,
        pfilename);
    
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_nglufilename);
        return;
    }
    
    // dg_forthloadfilestring
    dg_forthnglufilestring(pBHarrayhead);
    
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_nglufilename);
        return;
    }
}


void dg_fmslashmod(UINT64* pints)
//     pints points to a UINT64 array of 3 entries
//     notation: ( pints_array_in -- pints_array_out )
//     ( numeratorlo numeratorhi denominator -- remainder quotient denominator )
{
    UINT64 quotientsign = 0;
    UINT64 remaindersign = 0;

    // see if numerator is negative
    if (((INT64)(pints[1])) < 0)
    {
        quotientsign = ~quotientsign;

        // get absolute value of numerator
        // *((INT128*)pints) = -(*((INT128*)pints));
        dg_dnegate((INT64*)pints);
    }

    // check for divide by 0 error
    if (0 == pints[2])
    {
        if (0 == quotientsign)
        {
            // return max positive value
            pints[0] = 0x7FFFFFFFFFFFFFFF;
            pints[1] = 0x7FFFFFFFFFFFFFFF;
        }
        else
        {
            // return max negative value 
            pints[0] = 0x8000000000000000;
            pints[1] = 0x8000000000000000;
        }
        return;
    }

    // see if denominator is negative
    if (((INT64)(pints[2])) < 0)
    {
        quotientsign = ~quotientsign;

        //remainder gets same sign as denominator
        remaindersign = ~remaindersign;

        // get absolute value of denominator
        pints[2] = (UINT64)(-((INT64)(pints[2])));
    }

    // do divide
    dg_umslashmod(pints);

    // see if remainder is supposed to be negative
    if (remaindersign != 0)
    {
        pints[0] = (UINT64)(-((INT64)(pints[0])));
    }

    // see if quotient is supposed to be negative
    if (quotientsign != 0)
    {
        pints[1] = (UINT64)(-((INT64)(pints[1])));

        // if remainder is not 0, need to adjust result for flooring
        if (pints[0] != 0)
        {
            // adjust quotient flooring
            pints[1] -= 1; // unsigned

            // adjust remainder for flooring
            //  denominator is now absolute value of original denominator
            if (remaindersign != 0)
            {
                // remainder is negative, need rem = -denom - rem
                pints[0] = (UINT64)(-((INT64)(pints[2])) - ((INT64)(pints[0])));
            }
            else
            {
                // remainder is positive case, need rem = denom - rem
                pints[0] = pints[2] - pints[0];
            }
        }

        // check for negative overflow
        if (pints[1] < 0x8000000000000000)
        {
            // set quotient to max negative value
            pints[1] = 0x8000000000000000;

            // set remainder to max (impossible) value having correct sign
            if (remaindersign != 0)
            {
                pints[0] = 0x8000000000000000;
            }
            else
            {
                pints[0] = 0x7FFFFFFFFFFFFFFF;
            }
        }
    }
    else
    {
        // check for positive overflow
        if (pints[1] >= 0x8000000000000000)
        {
            // set quotient to max negative value
            pints[1] = 0x7FFFFFFFFFFFFFFF;

            // set remainder to max (impossible) value having correct sign
            if (remaindersign != 0)
            {
                pints[0] = 0x8000000000000000;
            }
            else
            {
                pints[0] = 0x7FFFFFFFFFFFFFFF;
            }
        }
    }
}

// did it this way for two reasons
//  1) its difficult to predict when an overflow will occur using IDIV
//  2) less assembly language routines makes it easier to port
void dg_smslashrem(UINT64* pints)
//     pints points to a UINT64 array of 3 entries
//     notation: ( pints_array_in -- pints_array_out )
//     ( numeratorlo numeratorhi denominator -- remainder quotient denominator )
{
    UINT64 quotientsign = 0;
    UINT64 remaindersign = 0;

    // see if numerator is negative
    if (((INT64)(pints[1])) < 0)
    {
        quotientsign = ~quotientsign;

        //remainder gets same sign as numerator
        remaindersign = ~remaindersign;
        // get absolute value of numerator
        // *((INT128*)pints) = -(*((INT128*)pints));
        dg_dnegate((INT64*)pints);
    }

    // check for divide by 0 error
    if (0 == pints[2])
    {
        if (0 == quotientsign)
        {
            // return max positive value
            pints[0] = 0x7FFFFFFFFFFFFFFF;
            pints[1] = 0x7FFFFFFFFFFFFFFF;
        }
        else
        {
            // return max negative value 
            pints[0] = 0x8000000000000000;
            pints[1] = 0x8000000000000000;
        }
        return;
    }

    // see if denominator is negative
    if (((INT64)(pints[2])) < 0)
    {
        quotientsign = ~quotientsign;
        // get absolute value of denominator
        pints[2] = (UINT64)(-((INT64)(pints[2])));
    }

    // do divide
    dg_umslashmod(pints);

    // see if remainder is supposed to be negative
    if (remaindersign != 0)
    {
        pints[0] = (UINT64)(-((INT64)(pints[0])));
    }

    // see if quotient is supposed to be negative
    if (quotientsign != 0)
    {
        pints[1] = (UINT64)(-((INT64)(pints[1])));

        // check for negative overflow
        if (pints[1] < 0x8000000000000000)
        {
            // set quotient to max negative value
            pints[1] = 0x8000000000000000;

            // set remainder to max (impossible) value having correct sign
            if (remaindersign != 0)
            {
                pints[0] = 0x8000000000000000;
            }
            else
            {
                pints[0] = 0x7FFFFFFFFFFFFFFF;
            }
        }
    }
    else
    {
        // check for positive overflow
        if (pints[1] >= 0x8000000000000000)
        {
            // set quotient to max negative value
            pints[1] = 0x7FFFFFFFFFFFFFFF;

            // set remainder to max (impossible) value having correct sign
            if (remaindersign != 0)
            {
                pints[0] = 0x8000000000000000;
            }
            else
            {
                pints[0] = 0x7FFFFFFFFFFFFFFF;
            }
        }
    }
}

// gonna assume these buffers are ok since they came from dg_getpbuffer just after init
 // user didn't have a chance to mess them up yet
 // (the value after slash should be diaperglu, diaperglu.exe, diaperglu.dll or scriptfilename.dglu)
UINT64 dg_checkformatchafterslash(
    unsigned char* pbufa,
    UINT64 bufalength,
    unsigned char* pbufb,
    UINT64 bufblength)
{
    UINT64 i, j;

    i = bufalength;
    j = bufblength;

    if ((0 == i) || (0 == j))
    {
        // empty strings are NOT matches
        // need the file names to match and for that there have to be files
        return (FORTH_FALSE);
    }

    // skipping null terminators
    if (0 == pbufa[i - 1])
    {
        i--;
    }

    if (0 == pbufb[j - 1])
    {
        j--;
    }

    if ((0 == i) || (0 == j))
    {
        // empty strings are NOT matches
        // need the file names to match and for that there have to be files
        return (FORTH_FALSE);
    }

    if (('/' == pbufa[i - 1]) || ('\\' == pbufa[i - 1]))
    {
        i--;
    }

    if (('/' == pbufb[j - 1]) || ('\\' == pbufb[j - 1]))
    {
        j--;
    }

    if ((0 == i) || (0 == j))
    {
        // empty strings are NOT matches
        // need the file names to match and for that there have to be files
        return (FORTH_FALSE);
    }

    while (true)
    {
        if ((0 == i) || (j == 0))
        {
            // one of the strings did not have a slash
            // in order to match, both i and j must be 0
            // or the one that is not 0 must have slash as next character
            if ((0 == i) && (0 == j))
            {
                return (FORTH_TRUE);
            }

            if (0 == i)
            {
                if (('/' == pbufb[j - 1]) || ('\\' == pbufb[j - 1]))
                {
                    return (FORTH_TRUE);
                }
                else
                {
                    return (FORTH_FALSE);
                }
            }

            // then j is 0

            if (('/' == pbufa[i - 1]) || ('\\' == pbufa[i - 1]))
            {
                return (FORTH_TRUE);
            }

            return (FORTH_FALSE);
        }

        // if one is a slash, the other must be a slash
        // otherwise they must match
        if (('/' == pbufa[i - 1]) || ('\\' == pbufa[i - 1]))
        {
            if (('/' == pbufb[j - 1]) || ('\\' == pbufb[j - 1]))
            {
                return (FORTH_TRUE);
            }
            else
            {
                return (FORTH_FALSE);
            }
        }

        if (pbufa[i - 1] != pbufb[j - 1])
        {
            return (FORTH_FALSE);
        }

        i--;
        j--;
    }
}

UINT64 dg_hibitd(
  UINT64 ulo,
  UINT64 uhi)
{
    UINT64 index;

    index = dg_hibit(uhi);

    if (index < 64)
    {
        return(index + 64);
    }

    index = dg_hibit(ulo);

    return (index);
}


