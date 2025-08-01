/*
    An implementation of Text I/O as defined by PEP 3116 - "New I/O"

    Classes defined here: TextIOBase, IncrementalNewlineDecoder, TextIOWrapper.

    Written by Amaury Forgeot d'Arc and Antoine Pitrou
*/

#include "Python.h"
#include "pycore_call.h"          // _PyObject_CallMethod()
#include "pycore_codecs.h"        // _PyCodecInfo_GetIncrementalDecoder()
#include "pycore_fileutils.h"     // _Py_GetLocaleEncoding()
#include "pycore_interp.h"        // PyInterpreterState.fs_codec
#include "pycore_long.h"          // _PyLong_GetZero()
#include "pycore_object.h"        // _PyObject_GC_UNTRACK()
#include "pycore_pyerrors.h"      // _PyErr_ChainExceptions1()
#include "pycore_pystate.h"       // _PyInterpreterState_GET()
#include "pycore_unicodeobject.h" // _PyUnicode_AsASCIIString()
#include "pycore_weakref.h"       // FT_CLEAR_WEAKREFS()

#include "_iomodule.h"

/*[clinic input]
module _io
class _io.IncrementalNewlineDecoder "nldecoder_object *" "clinic_state()->PyIncrementalNewlineDecoder_Type"
class _io.TextIOWrapper "textio *" "clinic_state()->TextIOWrapper_Type"
class _io._TextIOBase "PyObject *" "&PyTextIOBase_Type"
[clinic start generated code]*/
/*[clinic end generated code: output=da39a3ee5e6b4b0d input=8b7f24fa13bfdd7f]*/

typedef struct nldecoder_object nldecoder_object;
typedef struct textio textio;

#define clinic_state() (find_io_state_by_def(Py_TYPE(self)))
#include "clinic/textio.c.h"
#undef clinic_state

/* TextIOBase */

PyDoc_STRVAR(textiobase_doc,
    "Base class for text I/O.\n"
    "\n"
    "This class provides a character and line based interface to stream\n"
    "I/O. There is no readinto method because Python's character strings\n"
    "are immutable.\n"
    );

static PyObject *
_unsupported(_PyIO_State *state, const char *message)
{
    PyErr_SetString(state->unsupported_operation, message);
    return NULL;
}

/*[clinic input]
_io._TextIOBase.detach
    cls: defining_class
    /

Separate the underlying buffer from the TextIOBase and return it.

After the underlying buffer has been detached, the TextIO is in an unusable state.
[clinic start generated code]*/

static PyObject *
_io__TextIOBase_detach_impl(PyObject *self, PyTypeObject *cls)
/*[clinic end generated code: output=50915f40c609eaa4 input=987ca3640d0a3776]*/
{
    _PyIO_State *state = get_io_state_by_cls(cls);
    return _unsupported(state, "detach");
}

/*[clinic input]
_io._TextIOBase.read
    cls: defining_class
    size: int(unused=True) = -1
    /

Read at most size characters from stream.

Read from underlying buffer until we have size characters or we hit EOF.
If size is negative or omitted, read until EOF.
[clinic start generated code]*/

static PyObject *
_io__TextIOBase_read_impl(PyObject *self, PyTypeObject *cls,
                          int Py_UNUSED(size))
/*[clinic end generated code: output=51a5178a309ce647 input=f5e37720f9fc563f]*/
{
    _PyIO_State *state = get_io_state_by_cls(cls);
    return _unsupported(state, "read");
}

/*[clinic input]
_io._TextIOBase.readline
    cls: defining_class
    size: int(unused=True) = -1
    /

Read until newline or EOF.

Return an empty string if EOF is hit immediately.
If size is specified, at most size characters will be read.
[clinic start generated code]*/

static PyObject *
_io__TextIOBase_readline_impl(PyObject *self, PyTypeObject *cls,
                              int Py_UNUSED(size))
/*[clinic end generated code: output=3f47d7966d6d074e input=42eafec94107fa27]*/
{
    _PyIO_State *state = get_io_state_by_cls(cls);
    return _unsupported(state, "readline");
}

/*[clinic input]
_io._TextIOBase.write
    cls: defining_class
    s: str(unused=True)
    /

Write string s to stream.

Return the number of characters written
(which is always equal to the length of the string).
[clinic start generated code]*/

static PyObject *
_io__TextIOBase_write_impl(PyObject *self, PyTypeObject *cls,
                           const char *Py_UNUSED(s))
/*[clinic end generated code: output=18b28231460275de input=e9cabaa5f6732b07]*/
{
    _PyIO_State *state = get_io_state_by_cls(cls);
    return _unsupported(state, "write");
}

/*[clinic input]
@getter
_io._TextIOBase.encoding

Encoding of the text stream.

Subclasses should override.
[clinic start generated code]*/

static PyObject *
_io__TextIOBase_encoding_get_impl(PyObject *self)
/*[clinic end generated code: output=e0f5d8f548b92432 input=4736d7621dd38f43]*/
{
    Py_RETURN_NONE;
}

/*[clinic input]
@getter
_io._TextIOBase.newlines

Line endings translated so far.

Only line endings translated during reading are considered.

Subclasses should override.
[clinic start generated code]*/

static PyObject *
_io__TextIOBase_newlines_get_impl(PyObject *self)
/*[clinic end generated code: output=46ec147fb9f00c2a input=a5b196d076af1164]*/
{
    Py_RETURN_NONE;
}

/*[clinic input]
@getter
_io._TextIOBase.errors

The error setting of the decoder or encoder.

Subclasses should override.
[clinic start generated code]*/

static PyObject *
_io__TextIOBase_errors_get_impl(PyObject *self)
/*[clinic end generated code: output=c6623d6addcd087d input=974aa52d1db93a82]*/
{
    Py_RETURN_NONE;
}


static PyMethodDef textiobase_methods[] = {
    _IO__TEXTIOBASE_DETACH_METHODDEF
    _IO__TEXTIOBASE_READ_METHODDEF
    _IO__TEXTIOBASE_READLINE_METHODDEF
    _IO__TEXTIOBASE_WRITE_METHODDEF
    {NULL, NULL}
};

static PyGetSetDef textiobase_getset[] = {
    _IO__TEXTIOBASE_ENCODING_GETSETDEF
    _IO__TEXTIOBASE_NEWLINES_GETSETDEF
    _IO__TEXTIOBASE_ERRORS_GETSETDEF
    {NULL}
};

static PyType_Slot textiobase_slots[] = {
    {Py_tp_doc, (void *)textiobase_doc},
    {Py_tp_methods, textiobase_methods},
    {Py_tp_getset, textiobase_getset},
    {0, NULL},
};

/* Do not set Py_TPFLAGS_HAVE_GC so that tp_traverse and tp_clear are inherited */
PyType_Spec textiobase_spec = {
    .name = "_io._TextIOBase",
    .flags = (Py_TPFLAGS_DEFAULT | Py_TPFLAGS_BASETYPE |
              Py_TPFLAGS_IMMUTABLETYPE),
    .slots = textiobase_slots,
};

/* IncrementalNewlineDecoder */

struct nldecoder_object {
    PyObject_HEAD
    PyObject *decoder;
    PyObject *errors;
    unsigned int pendingcr: 1;
    unsigned int translate: 1;
    unsigned int seennl: 3;
};

#define nldecoder_object_CAST(op)   ((nldecoder_object *)(op))

/*[clinic input]
_io.IncrementalNewlineDecoder.__init__
    decoder: object
    translate: bool
    errors: object(c_default="NULL") = "strict"

Codec used when reading a file in universal newlines mode.

It wraps another incremental decoder, translating \r\n and \r into \n.
It also records the types of newlines encountered.  When used with
translate=False, it ensures that the newline sequence is returned in
one piece. When used with decoder=None, it expects unicode strings as
decode input and translates newlines without first invoking an external
decoder.
[clinic start generated code]*/

static int
_io_IncrementalNewlineDecoder___init___impl(nldecoder_object *self,
                                            PyObject *decoder, int translate,
                                            PyObject *errors)
/*[clinic end generated code: output=fbd04d443e764ec2 input=ed547aa257616b0e]*/
{

    if (errors == NULL) {
        errors = &_Py_ID(strict);
    }
    else {
        errors = Py_NewRef(errors);
    }

    Py_XSETREF(self->errors, errors);
    Py_XSETREF(self->decoder, Py_NewRef(decoder));
    self->translate = translate ? 1 : 0;
    self->seennl = 0;
    self->pendingcr = 0;

    return 0;
}

static int
incrementalnewlinedecoder_traverse(PyObject *op, visitproc visit, void *arg)
{
    nldecoder_object *self = nldecoder_object_CAST(op);
    Py_VISIT(Py_TYPE(self));
    Py_VISIT(self->decoder);
    Py_VISIT(self->errors);
    return 0;
}

static int
incrementalnewlinedecoder_clear(PyObject *op)
{
    nldecoder_object *self = nldecoder_object_CAST(op);
    Py_CLEAR(self->decoder);
    Py_CLEAR(self->errors);
    return 0;
}

static void
incrementalnewlinedecoder_dealloc(PyObject *op)
{
    nldecoder_object *self = nldecoder_object_CAST(op);
    PyTypeObject *tp = Py_TYPE(self);
    _PyObject_GC_UNTRACK(self);
    (void)incrementalnewlinedecoder_clear(op);
    tp->tp_free(self);
    Py_DECREF(tp);
}

static int
check_decoded(PyObject *decoded)
{
    if (decoded == NULL)
        return -1;
    if (!PyUnicode_Check(decoded)) {
        PyErr_Format(PyExc_TypeError,
                     "decoder should return a string result, not '%.200s'",
                     Py_TYPE(decoded)->tp_name);
        Py_DECREF(decoded);
        return -1;
    }
    return 0;
}

#define CHECK_INITIALIZED_DECODER(self) \
    if (self->errors == NULL) { \
        PyErr_SetString(PyExc_ValueError, \
                        "IncrementalNewlineDecoder.__init__() not called"); \
        return NULL; \
    }

#define SEEN_CR   1
#define SEEN_LF   2
#define SEEN_CRLF 4
#define SEEN_ALL (SEEN_CR | SEEN_LF | SEEN_CRLF)

PyObject *
_PyIncrementalNewlineDecoder_decode(PyObject *myself,
                                    PyObject *input, int final)
{
    PyObject *output;
    Py_ssize_t output_len;
    nldecoder_object *self = nldecoder_object_CAST(myself);

    CHECK_INITIALIZED_DECODER(self);

    /* decode input (with the eventual \r from a previous pass) */
    if (self->decoder != Py_None) {
        output = PyObject_CallMethodObjArgs(self->decoder,
            &_Py_ID(decode), input, final ? Py_True : Py_False, NULL);
    }
    else {
        output = Py_NewRef(input);
    }

    if (check_decoded(output) < 0)
        return NULL;

    output_len = PyUnicode_GET_LENGTH(output);
    if (self->pendingcr && (final || output_len > 0)) {
        /* Prefix output with CR */
        int kind;
        PyObject *modified;
        char *out;

        modified = PyUnicode_New(output_len + 1,
                                 PyUnicode_MAX_CHAR_VALUE(output));
        if (modified == NULL)
            goto error;
        kind = PyUnicode_KIND(modified);
        out = PyUnicode_DATA(modified);
        PyUnicode_WRITE(kind, out, 0, '\r');
        memcpy(out + kind, PyUnicode_DATA(output), kind * output_len);
        Py_SETREF(output, modified);
        self->pendingcr = 0;
        output_len++;
    }

    /* retain last \r even when not translating data:
     * then readline() is sure to get \r\n in one pass
     */
    if (!final) {
        if (output_len > 0
            && PyUnicode_READ_CHAR(output, output_len - 1) == '\r')
        {
            PyObject *modified = PyUnicode_Substring(output, 0, output_len -1);
            if (modified == NULL)
                goto error;
            Py_SETREF(output, modified);
            self->pendingcr = 1;
        }
    }

    /* Record which newlines are read and do newline translation if desired,
       all in one pass. */
    {
        const void *in_str;
        Py_ssize_t len;
        int seennl = self->seennl;
        int only_lf = 0;
        int kind;

        in_str = PyUnicode_DATA(output);
        len = PyUnicode_GET_LENGTH(output);
        kind = PyUnicode_KIND(output);

        if (len == 0)
            return output;

        /* If, up to now, newlines are consistently \n, do a quick check
           for the \r *byte* with the libc's optimized memchr.
           */
        if (seennl == SEEN_LF || seennl == 0) {
            only_lf = (memchr(in_str, '\r', kind * len) == NULL);
        }

        if (only_lf) {
            /* If not already seen, quick scan for a possible "\n" character.
               (there's nothing else to be done, even when in translation mode)
            */
            if (seennl == 0 &&
                memchr(in_str, '\n', kind * len) != NULL) {
                if (kind == PyUnicode_1BYTE_KIND)
                    seennl |= SEEN_LF;
                else {
                    Py_ssize_t i = 0;
                    for (;;) {
                        Py_UCS4 c;
                        /* Fast loop for non-control characters */
                        while (PyUnicode_READ(kind, in_str, i) > '\n')
                            i++;
                        c = PyUnicode_READ(kind, in_str, i++);
                        if (c == '\n') {
                            seennl |= SEEN_LF;
                            break;
                        }
                        if (i >= len)
                            break;
                    }
                }
            }
            /* Finished: we have scanned for newlines, and none of them
               need translating */
        }
        else if (!self->translate) {
            Py_ssize_t i = 0;
            /* We have already seen all newline types, no need to scan again */
            if (seennl == SEEN_ALL)
                goto endscan;
            for (;;) {
                Py_UCS4 c;
                /* Fast loop for non-control characters */
                while (PyUnicode_READ(kind, in_str, i) > '\r')
                    i++;
                c = PyUnicode_READ(kind, in_str, i++);
                if (c == '\n')
                    seennl |= SEEN_LF;
                else if (c == '\r') {
                    if (PyUnicode_READ(kind, in_str, i) == '\n') {
                        seennl |= SEEN_CRLF;
                        i++;
                    }
                    else
                        seennl |= SEEN_CR;
                }
                if (i >= len)
                    break;
                if (seennl == SEEN_ALL)
                    break;
            }
        endscan:
            ;
        }
        else {
            void *translated;
            int kind = PyUnicode_KIND(output);
            const void *in_str = PyUnicode_DATA(output);
            Py_ssize_t in, out;
            /* XXX: Previous in-place translation here is disabled as
               resizing is not possible anymore */
            /* We could try to optimize this so that we only do a copy
               when there is something to translate. On the other hand,
               we already know there is a \r byte, so chances are high
               that something needs to be done. */
            translated = PyMem_Malloc(kind * len);
            if (translated == NULL) {
                PyErr_NoMemory();
                goto error;
            }
            in = out = 0;
            for (;;) {
                Py_UCS4 c;
                /* Fast loop for non-control characters */
                while ((c = PyUnicode_READ(kind, in_str, in++)) > '\r')
                    PyUnicode_WRITE(kind, translated, out++, c);
                if (c == '\n') {
                    PyUnicode_WRITE(kind, translated, out++, c);
                    seennl |= SEEN_LF;
                    continue;
                }
                if (c == '\r') {
                    if (PyUnicode_READ(kind, in_str, in) == '\n') {
                        in++;
                        seennl |= SEEN_CRLF;
                    }
                    else
                        seennl |= SEEN_CR;
                    PyUnicode_WRITE(kind, translated, out++, '\n');
                    continue;
                }
                if (in > len)
                    break;
                PyUnicode_WRITE(kind, translated, out++, c);
            }
            Py_DECREF(output);
            output = PyUnicode_FromKindAndData(kind, translated, out);
            PyMem_Free(translated);
            if (!output)
                return NULL;
        }
        self->seennl |= seennl;
    }

    return output;

  error:
    Py_DECREF(output);
    return NULL;
}

/*[clinic input]
_io.IncrementalNewlineDecoder.decode
    input: object
    final: bool = False
[clinic start generated code]*/

static PyObject *
_io_IncrementalNewlineDecoder_decode_impl(nldecoder_object *self,
                                          PyObject *input, int final)
/*[clinic end generated code: output=0d486755bb37a66e input=90e223c70322c5cd]*/
{
    return _PyIncrementalNewlineDecoder_decode((PyObject *) self, input, final);
}

/*[clinic input]
_io.IncrementalNewlineDecoder.getstate
[clinic start generated code]*/

static PyObject *
_io_IncrementalNewlineDecoder_getstate_impl(nldecoder_object *self)
/*[clinic end generated code: output=f0d2c9c136f4e0d0 input=f8ff101825e32e7f]*/
{
    PyObject *buffer;
    unsigned long long flag;

    CHECK_INITIALIZED_DECODER(self);

    if (self->decoder != Py_None) {
        PyObject *state = PyObject_CallMethodNoArgs(self->decoder,
           &_Py_ID(getstate));
        if (state == NULL)
            return NULL;
        if (!PyTuple_Check(state)) {
            PyErr_SetString(PyExc_TypeError,
                            "illegal decoder state");
            Py_DECREF(state);
            return NULL;
        }
        if (!PyArg_ParseTuple(state, "OK;illegal decoder state",
                              &buffer, &flag))
        {
            Py_DECREF(state);
            return NULL;
        }
        Py_INCREF(buffer);
        Py_DECREF(state);
    }
    else {
        buffer = Py_GetConstant(Py_CONSTANT_EMPTY_BYTES);
        flag = 0;
    }
    flag <<= 1;
    if (self->pendingcr)
        flag |= 1;
    return Py_BuildValue("NK", buffer, flag);
}

/*[clinic input]
_io.IncrementalNewlineDecoder.setstate
    state: object
    /
[clinic start generated code]*/

static PyObject *
_io_IncrementalNewlineDecoder_setstate_impl(nldecoder_object *self,
                                            PyObject *state)
/*[clinic end generated code: output=09135cb6e78a1dc8 input=c53fb505a76dbbe2]*/
{
    PyObject *buffer;
    unsigned long long flag;

    CHECK_INITIALIZED_DECODER(self);

    if (!PyTuple_Check(state)) {
        PyErr_SetString(PyExc_TypeError, "state argument must be a tuple");
        return NULL;
    }
    if (!PyArg_ParseTuple(state, "OK;setstate(): illegal state argument",
                          &buffer, &flag))
    {
        return NULL;
    }

    self->pendingcr = (int) (flag & 1);
    flag >>= 1;

    if (self->decoder != Py_None) {
        return _PyObject_CallMethod(self->decoder, &_Py_ID(setstate),
                                    "((OK))", buffer, flag);
    }
    else {
        Py_RETURN_NONE;
    }
}

/*[clinic input]
_io.IncrementalNewlineDecoder.reset
[clinic start generated code]*/

static PyObject *
_io_IncrementalNewlineDecoder_reset_impl(nldecoder_object *self)
/*[clinic end generated code: output=32fa40c7462aa8ff input=728678ddaea776df]*/
{
    CHECK_INITIALIZED_DECODER(self);

    self->seennl = 0;
    self->pendingcr = 0;
    if (self->decoder != Py_None)
        return PyObject_CallMethodNoArgs(self->decoder, &_Py_ID(reset));
    else
        Py_RETURN_NONE;
}

static PyObject *
incrementalnewlinedecoder_newlines_get(PyObject *op, void *Py_UNUSED(context))
{
    nldecoder_object *self = nldecoder_object_CAST(op);
    CHECK_INITIALIZED_DECODER(self);

    switch (self->seennl) {
    case SEEN_CR:
        return PyUnicode_FromString("\r");
    case SEEN_LF:
        return PyUnicode_FromString("\n");
    case SEEN_CRLF:
        return PyUnicode_FromString("\r\n");
    case SEEN_CR | SEEN_LF:
        return Py_BuildValue("ss", "\r", "\n");
    case SEEN_CR | SEEN_CRLF:
        return Py_BuildValue("ss", "\r", "\r\n");
    case SEEN_LF | SEEN_CRLF:
        return Py_BuildValue("ss", "\n", "\r\n");
    case SEEN_CR | SEEN_LF | SEEN_CRLF:
        return Py_BuildValue("sss", "\r", "\n", "\r\n");
    default:
        Py_RETURN_NONE;
   }

}

/* TextIOWrapper */

typedef PyObject *(*encodefunc_t)(PyObject *, PyObject *);

struct textio
{
    PyObject_HEAD
    int ok; /* initialized? */
    int detached;
    Py_ssize_t chunk_size;
    PyObject *buffer;
    PyObject *encoding;
    PyObject *encoder;
    PyObject *decoder;
    PyObject *readnl;
    PyObject *errors;
    const char *writenl; /* ASCII-encoded; NULL stands for \n */
    char line_buffering;
    char write_through;
    char readuniversal;
    char readtranslate;
    char writetranslate;
    char seekable;
    char has_read1;
    char telling;
    char finalizing;
    /* Specialized encoding func (see below) */
    encodefunc_t encodefunc;
    /* Whether or not it's the start of the stream */
    char encoding_start_of_stream;

    /* Reads and writes are internally buffered in order to speed things up.
       However, any read will first flush the write buffer if itsn't empty.

       Please also note that text to be written is first encoded before being
       buffered. This is necessary so that encoding errors are immediately
       reported to the caller, but it unfortunately means that the
       IncrementalEncoder (whose encode() method is always written in Python)
       becomes a bottleneck for small writes.
    */
    PyObject *decoded_chars;       /* buffer for text returned from decoder */
    Py_ssize_t decoded_chars_used; /* offset into _decoded_chars for read() */
    PyObject *pending_bytes;       // data waiting to be written.
                                   // ascii unicode, bytes, or list of them.
    Py_ssize_t pending_bytes_count;

    /* snapshot is either NULL, or a tuple (dec_flags, next_input) where
     * dec_flags is the second (integer) item of the decoder state and
     * next_input is the chunk of input bytes that comes next after the
     * snapshot point.  We use this to reconstruct decoder states in tell().
     */
    PyObject *snapshot;
    /* Bytes-to-characters ratio for the current chunk. Serves as input for
       the heuristic in tell(). */
    double b2cratio;

    /* Cache raw object if it's a FileIO object */
    PyObject *raw;

    PyObject *weakreflist;
    PyObject *dict;

    _PyIO_State *state;
};

#define textio_CAST(op) ((textio *)(op))

static void
textiowrapper_set_decoded_chars(textio *self, PyObject *chars);

/* A couple of specialized cases in order to bypass the slow incremental
   encoding methods for the most popular encodings. */

static PyObject *
ascii_encode(PyObject *op, PyObject *text)
{
    textio *self = textio_CAST(op);
    return _PyUnicode_AsASCIIString(text, PyUnicode_AsUTF8(self->errors));
}

static PyObject *
utf16be_encode(PyObject *op, PyObject *text)
{
    textio *self = textio_CAST(op);
    return _PyUnicode_EncodeUTF16(text, PyUnicode_AsUTF8(self->errors), 1);
}

static PyObject *
utf16le_encode(PyObject *op, PyObject *text)
{
    textio *self = textio_CAST(op);
    return _PyUnicode_EncodeUTF16(text, PyUnicode_AsUTF8(self->errors), -1);
}

static PyObject *
utf16_encode(PyObject *op, PyObject *text)
{
    textio *self = textio_CAST(op);
    if (!self->encoding_start_of_stream) {
        /* Skip the BOM and use native byte ordering */
#if PY_BIG_ENDIAN
        return utf16be_encode(op, text);
#else
        return utf16le_encode(op, text);
#endif
    }
    return _PyUnicode_EncodeUTF16(text, PyUnicode_AsUTF8(self->errors), 0);
}

static PyObject *
utf32be_encode(PyObject *op, PyObject *text)
{
    textio *self = textio_CAST(op);
    return _PyUnicode_EncodeUTF32(text, PyUnicode_AsUTF8(self->errors), 1);
}

static PyObject *
utf32le_encode(PyObject *op, PyObject *text)
{
    textio *self = textio_CAST(op);
    return _PyUnicode_EncodeUTF32(text, PyUnicode_AsUTF8(self->errors), -1);
}

static PyObject *
utf32_encode(PyObject *op, PyObject *text)
{
    textio *self = textio_CAST(op);
    if (!self->encoding_start_of_stream) {
        /* Skip the BOM and use native byte ordering */
#if PY_BIG_ENDIAN
        return utf32be_encode(op, text);
#else
        return utf32le_encode(op, text);
#endif
    }
    return _PyUnicode_EncodeUTF32(text, PyUnicode_AsUTF8(self->errors), 0);
}

static PyObject *
utf8_encode(PyObject *op, PyObject *text)
{
    textio *self = textio_CAST(op);
    return _PyUnicode_AsUTF8String(text, PyUnicode_AsUTF8(self->errors));
}

static PyObject *
latin1_encode(PyObject *op, PyObject *text)
{
    textio *self = textio_CAST(op);
    return _PyUnicode_AsLatin1String(text, PyUnicode_AsUTF8(self->errors));
}

// Return true when encoding can be skipped when text is ascii.
static inline int
is_asciicompat_encoding(encodefunc_t f)
{
    return f == ascii_encode || f == latin1_encode || f == utf8_encode;
}

/* Map normalized encoding names onto the specialized encoding funcs */

typedef struct {
    const char *name;
    encodefunc_t encodefunc;
} encodefuncentry;

static const encodefuncentry encodefuncs[] = {
    {"ascii",       ascii_encode},
    {"iso8859-1",   latin1_encode},
    {"utf-8",       utf8_encode},
    {"utf-16-be",   utf16be_encode},
    {"utf-16-le",   utf16le_encode},
    {"utf-16",      utf16_encode},
    {"utf-32-be",   utf32be_encode},
    {"utf-32-le",   utf32le_encode},
    {"utf-32",      utf32_encode},
    {NULL, NULL}
};

static int
validate_newline(const char *newline)
{
    if (newline && newline[0] != '\0'
        && !(newline[0] == '\n' && newline[1] == '\0')
        && !(newline[0] == '\r' && newline[1] == '\0')
        && !(newline[0] == '\r' && newline[1] == '\n' && newline[2] == '\0')) {
        PyErr_Format(PyExc_ValueError,
                     "illegal newline value: %s", newline);
        return -1;
    }
    return 0;
}

static int
set_newline(textio *self, const char *newline)
{
    PyObject *old = self->readnl;
    if (newline == NULL) {
        self->readnl = NULL;
    }
    else {
        self->readnl = PyUnicode_FromString(newline);
        if (self->readnl == NULL) {
            self->readnl = old;
            return -1;
        }
    }
    self->readuniversal = (newline == NULL || newline[0] == '\0');
    self->readtranslate = (newline == NULL);
    self->writetranslate = (newline == NULL || newline[0] != '\0');
    if (!self->readuniversal && self->readnl != NULL) {
        // validate_newline() accepts only ASCII newlines.
        assert(PyUnicode_KIND(self->readnl) == PyUnicode_1BYTE_KIND);
        self->writenl = (const char *)PyUnicode_1BYTE_DATA(self->readnl);
        if (strcmp(self->writenl, "\n") == 0) {
            self->writenl = NULL;
        }
    }
    else {
#ifdef MS_WINDOWS
        self->writenl = "\r\n";
#else
        self->writenl = NULL;
#endif
    }
    Py_XDECREF(old);
    return 0;
}

static int
_textiowrapper_set_decoder(textio *self, PyObject *codec_info,
                           const char *errors)
{
    PyObject *res;
    int r;

    res = PyObject_CallMethodNoArgs(self->buffer, &_Py_ID(readable));
    if (res == NULL)
        return -1;

    r = PyObject_IsTrue(res);
    Py_DECREF(res);
    if (r == -1)
        return -1;

    if (r != 1)
        return 0;

    Py_CLEAR(self->decoder);
    self->decoder = _PyCodecInfo_GetIncrementalDecoder(codec_info, errors);
    if (self->decoder == NULL)
        return -1;

    if (self->readuniversal) {
        _PyIO_State *state = self->state;
        PyObject *incrementalDecoder = PyObject_CallFunctionObjArgs(
            (PyObject *)state->PyIncrementalNewlineDecoder_Type,
            self->decoder, self->readtranslate ? Py_True : Py_False, NULL);
        if (incrementalDecoder == NULL)
            return -1;
        Py_XSETREF(self->decoder, incrementalDecoder);
    }

    return 0;
}

static PyObject*
_textiowrapper_decode(_PyIO_State *state, PyObject *decoder, PyObject *bytes,
                      int eof)
{
    PyObject *chars;

    if (Py_IS_TYPE(decoder, state->PyIncrementalNewlineDecoder_Type))
        chars = _PyIncrementalNewlineDecoder_decode(decoder, bytes, eof);
    else
        chars = PyObject_CallMethodObjArgs(decoder, &_Py_ID(decode), bytes,
                                           eof ? Py_True : Py_False, NULL);

    if (check_decoded(chars) < 0)
        // check_decoded already decreases refcount
        return NULL;

    return chars;
}

static int
_textiowrapper_set_encoder(textio *self, PyObject *codec_info,
                           const char *errors)
{
    PyObject *res;
    int r;

    res = PyObject_CallMethodNoArgs(self->buffer, &_Py_ID(writable));
    if (res == NULL)
        return -1;

    r = PyObject_IsTrue(res);
    Py_DECREF(res);
    if (r == -1)
        return -1;

    if (r != 1)
        return 0;

    Py_CLEAR(self->encoder);
    self->encodefunc = NULL;
    self->encoder = _PyCodecInfo_GetIncrementalEncoder(codec_info, errors);
    if (self->encoder == NULL)
        return -1;

    /* Get the normalized named of the codec */
    if (PyObject_GetOptionalAttr(codec_info, &_Py_ID(name), &res) < 0) {
        return -1;
    }
    if (res != NULL && PyUnicode_Check(res)) {
        const encodefuncentry *e = encodefuncs;
        while (e->name != NULL) {
            if (_PyUnicode_EqualToASCIIString(res, e->name)) {
                self->encodefunc = e->encodefunc;
                break;
            }
            e++;
        }
    }
    Py_XDECREF(res);

    return 0;
}

static int
_textiowrapper_fix_encoder_state(textio *self)
{
    if (!self->seekable || !self->encoder) {
        return 0;
    }

    self->encoding_start_of_stream = 1;

    PyObject *cookieObj = PyObject_CallMethodNoArgs(
        self->buffer, &_Py_ID(tell));
    if (cookieObj == NULL) {
        return -1;
    }

    int cmp = PyObject_RichCompareBool(cookieObj, _PyLong_GetZero(), Py_EQ);
    Py_DECREF(cookieObj);
    if (cmp < 0) {
        return -1;
    }

    if (cmp == 0) {
        self->encoding_start_of_stream = 0;
        PyObject *res = PyObject_CallMethodOneArg(
            self->encoder, &_Py_ID(setstate), _PyLong_GetZero());
        if (res == NULL) {
            return -1;
        }
        Py_DECREF(res);
    }

    return 0;
}

static int
io_check_errors(PyObject *errors)
{
    assert(errors != NULL && errors != Py_None);

    PyInterpreterState *interp = _PyInterpreterState_GET();
#ifndef Py_DEBUG
    /* In release mode, only check in development mode (-X dev) */
    if (!_PyInterpreterState_GetConfig(interp)->dev_mode) {
        return 0;
    }
#else
    /* Always check in debug mode */
#endif

    /* Avoid calling PyCodec_LookupError() before the codec registry is ready:
       before_PyUnicode_InitEncodings() is called. */
    if (!interp->unicode.fs_codec.encoding) {
        return 0;
    }

    const char *name = _PyUnicode_AsUTF8NoNUL(errors);
    if (name == NULL) {
        return -1;
    }
    PyObject *handler = PyCodec_LookupError(name);
    if (handler != NULL) {
        Py_DECREF(handler);
        return 0;
    }
    return -1;
}



/*[clinic input]
_io.TextIOWrapper.__init__
    buffer: object
    encoding: str(accept={str, NoneType}) = None
    errors: object = None
    newline: str(accept={str, NoneType}) = None
    line_buffering: bool = False
    write_through: bool = False

Character and line based layer over a BufferedIOBase object, buffer.

encoding gives the name of the encoding that the stream will be
decoded or encoded with. It defaults to locale.getencoding().

errors determines the strictness of encoding and decoding (see
help(codecs.Codec) or the documentation for codecs.register) and
defaults to "strict".

newline controls how line endings are handled. It can be None, '',
'\n', '\r', and '\r\n'.  It works as follows:

* On input, if newline is None, universal newlines mode is
  enabled. Lines in the input can end in '\n', '\r', or '\r\n', and
  these are translated into '\n' before being returned to the
  caller. If it is '', universal newline mode is enabled, but line
  endings are returned to the caller untranslated. If it has any of
  the other legal values, input lines are only terminated by the given
  string, and the line ending is returned to the caller untranslated.

* On output, if newline is None, any '\n' characters written are
  translated to the system default line separator, os.linesep. If
  newline is '' or '\n', no translation takes place. If newline is any
  of the other legal values, any '\n' characters written are translated
  to the given string.

If line_buffering is True, a call to flush is implied when a call to
write contains a newline character.
[clinic start generated code]*/

static int
_io_TextIOWrapper___init___impl(textio *self, PyObject *buffer,
                                const char *encoding, PyObject *errors,
                                const char *newline, int line_buffering,
                                int write_through)
/*[clinic end generated code: output=72267c0c01032ed2 input=e6cfaaaf6059d4f5]*/
{
    PyObject *raw, *codec_info = NULL;
    PyObject *res;
    int r;

    self->ok = 0;
    self->detached = 0;

    if (encoding == NULL) {
        PyInterpreterState *interp = _PyInterpreterState_GET();
        if (_PyInterpreterState_GetConfig(interp)->warn_default_encoding) {
            if (PyErr_WarnEx(PyExc_EncodingWarning,
                             "'encoding' argument not specified", 1)) {
                return -1;
            }
        }
    }

    if (errors == Py_None) {
        errors = &_Py_ID(strict);
    }
    else if (!PyUnicode_Check(errors)) {
        // Check 'errors' argument here because Argument Clinic doesn't support
        // 'str(accept={str, NoneType})' converter.
        PyErr_Format(
            PyExc_TypeError,
            "TextIOWrapper() argument 'errors' must be str or None, not %.50s",
            Py_TYPE(errors)->tp_name);
        return -1;
    }
    else if (io_check_errors(errors)) {
        return -1;
    }
    const char *errors_str = _PyUnicode_AsUTF8NoNUL(errors);
    if (errors_str == NULL) {
        return -1;
    }

    if (validate_newline(newline) < 0) {
        return -1;
    }

    Py_CLEAR(self->buffer);
    Py_CLEAR(self->encoding);
    Py_CLEAR(self->encoder);
    Py_CLEAR(self->decoder);
    Py_CLEAR(self->readnl);
    Py_CLEAR(self->decoded_chars);
    Py_CLEAR(self->pending_bytes);
    Py_CLEAR(self->snapshot);
    Py_CLEAR(self->errors);
    Py_CLEAR(self->raw);
    self->decoded_chars_used = 0;
    self->pending_bytes_count = 0;
    self->encodefunc = NULL;
    self->b2cratio = 0.0;

    if (encoding == NULL && _PyRuntime.preconfig.utf8_mode) {
        _Py_DECLARE_STR(utf_8, "utf-8");
        self->encoding = &_Py_STR(utf_8);
    }
    else if (encoding == NULL || (strcmp(encoding, "locale") == 0)) {
        self->encoding = _Py_GetLocaleEncodingObject();
        if (self->encoding == NULL) {
            goto error;
        }
        assert(PyUnicode_Check(self->encoding));
    }

    if (self->encoding != NULL) {
        encoding = PyUnicode_AsUTF8(self->encoding);
        if (encoding == NULL)
            goto error;
    }
    else if (encoding != NULL) {
        self->encoding = PyUnicode_FromString(encoding);
        if (self->encoding == NULL)
            goto error;
    }
    else {
        PyErr_SetString(PyExc_OSError,
                        "could not determine default encoding");
        goto error;
    }

    /* Check we have been asked for a real text encoding */
    codec_info = _PyCodec_LookupTextEncoding(encoding, NULL);
    if (codec_info == NULL) {
        Py_CLEAR(self->encoding);
        goto error;
    }

    /* XXX: Failures beyond this point have the potential to leak elements
     * of the partially constructed object (like self->encoding)
     */

    self->errors = Py_NewRef(errors);
    self->chunk_size = 8192;
    self->line_buffering = line_buffering;
    self->write_through = write_through;
    if (set_newline(self, newline) < 0) {
        goto error;
    }

    self->buffer = Py_NewRef(buffer);

    /* Build the decoder object */
    _PyIO_State *state = find_io_state_by_def(Py_TYPE(self));
    self->state = state;
    if (_textiowrapper_set_decoder(self, codec_info, errors_str) != 0)
        goto error;

    /* Build the encoder object */
    if (_textiowrapper_set_encoder(self, codec_info, errors_str) != 0)
        goto error;

    /* Finished sorting out the codec details */
    Py_CLEAR(codec_info);

    if (Py_IS_TYPE(buffer, state->PyBufferedReader_Type) ||
        Py_IS_TYPE(buffer, state->PyBufferedWriter_Type) ||
        Py_IS_TYPE(buffer, state->PyBufferedRandom_Type))
    {
        if (PyObject_GetOptionalAttr(buffer, &_Py_ID(raw), &raw) < 0)
            goto error;
        /* Cache the raw FileIO object to speed up 'closed' checks */
        if (raw != NULL) {
            if (Py_IS_TYPE(raw, state->PyFileIO_Type))
                self->raw = raw;
            else
                Py_DECREF(raw);
        }
    }

    res = PyObject_CallMethodNoArgs(buffer, &_Py_ID(seekable));
    if (res == NULL)
        goto error;
    r = PyObject_IsTrue(res);
    Py_DECREF(res);
    if (r < 0)
        goto error;
    self->seekable = self->telling = r;

    r = PyObject_HasAttrWithError(buffer, &_Py_ID(read1));
    if (r < 0) {
        goto error;
    }
    self->has_read1 = r;

    self->encoding_start_of_stream = 0;
    if (_textiowrapper_fix_encoder_state(self) < 0) {
        goto error;
    }

    self->ok = 1;
    return 0;

  error:
    Py_XDECREF(codec_info);
    return -1;
}

/* Return *default_value* if ob is None, 0 if ob is false, 1 if ob is true,
 * -1 on error.
 */
static int
convert_optional_bool(PyObject *obj, int default_value)
{
    long v;
    if (obj == Py_None) {
        v = default_value;
    }
    else {
        v = PyLong_AsLong(obj);
        if (v == -1 && PyErr_Occurred())
            return -1;
    }
    return v != 0;
}

static int
textiowrapper_change_encoding(textio *self, PyObject *encoding,
                              PyObject *errors, int newline_changed)
{
    /* Use existing settings where new settings are not specified */
    if (encoding == Py_None && errors == Py_None && !newline_changed) {
        return 0;  // no change
    }

    if (encoding == Py_None) {
        encoding = self->encoding;
        if (errors == Py_None) {
            errors = self->errors;
        }
        Py_INCREF(encoding);
    }
    else {
        if (_PyUnicode_EqualToASCIIString(encoding, "locale")) {
            encoding = _Py_GetLocaleEncodingObject();
            if (encoding == NULL) {
                return -1;
            }
        } else {
            Py_INCREF(encoding);
        }
        if (errors == Py_None) {
            errors = &_Py_ID(strict);
        }
    }
    Py_INCREF(errors);

    const char *c_encoding = PyUnicode_AsUTF8(encoding);
    if (c_encoding == NULL) {
        Py_DECREF(encoding);
        Py_DECREF(errors);
        return -1;
    }
    const char *c_errors = PyUnicode_AsUTF8(errors);
    if (c_errors == NULL) {
        Py_DECREF(encoding);
        Py_DECREF(errors);
        return -1;
    }

    // Create new encoder & decoder
    PyObject *codec_info = _PyCodec_LookupTextEncoding(c_encoding, NULL);
    if (codec_info == NULL) {
        Py_DECREF(encoding);
        Py_DECREF(errors);
        return -1;
    }
    if (_textiowrapper_set_decoder(self, codec_info, c_errors) != 0 ||
            _textiowrapper_set_encoder(self, codec_info, c_errors) != 0) {
        Py_DECREF(codec_info);
        Py_DECREF(encoding);
        Py_DECREF(errors);
        return -1;
    }
    Py_DECREF(codec_info);

    Py_SETREF(self->encoding, encoding);
    Py_SETREF(self->errors, errors);

    return _textiowrapper_fix_encoder_state(self);
}

/*[clinic input]
@critical_section
_io.TextIOWrapper.reconfigure
    *
    encoding: object = None
    errors: object = None
    newline as newline_obj: object(c_default="NULL") = None
    line_buffering as line_buffering_obj: object = None
    write_through as write_through_obj: object = None

Reconfigure the text stream with new parameters.

This also does an implicit stream flush.

[clinic start generated code]*/

static PyObject *
_io_TextIOWrapper_reconfigure_impl(textio *self, PyObject *encoding,
                                   PyObject *errors, PyObject *newline_obj,
                                   PyObject *line_buffering_obj,
                                   PyObject *write_through_obj)
/*[clinic end generated code: output=52b812ff4b3d4b0f input=dc3bd35ebda702a7]*/
{
    int line_buffering;
    int write_through;
    const char *newline = NULL;

    if (encoding != Py_None && !PyUnicode_Check(encoding)) {
        PyErr_Format(PyExc_TypeError,
                "reconfigure() argument 'encoding' must be str or None, not %s",
                Py_TYPE(encoding)->tp_name);
        return NULL;
    }
    if (errors != Py_None && !PyUnicode_Check(errors)) {
        PyErr_Format(PyExc_TypeError,
                "reconfigure() argument 'errors' must be str or None, not %s",
                Py_TYPE(errors)->tp_name);
        return NULL;
    }
    if (newline_obj != NULL && newline_obj != Py_None &&
        !PyUnicode_Check(newline_obj))
    {
        PyErr_Format(PyExc_TypeError,
                "reconfigure() argument 'newline' must be str or None, not %s",
                Py_TYPE(newline_obj)->tp_name);
        return NULL;
    }
    /* Check if something is in the read buffer */
    if (self->decoded_chars != NULL) {
        if (encoding != Py_None || errors != Py_None || newline_obj != NULL) {
            _unsupported(self->state,
                         "It is not possible to set the encoding or newline "
                         "of stream after the first read");
            return NULL;
        }
    }

    if (newline_obj != NULL && newline_obj != Py_None) {
        newline = PyUnicode_AsUTF8(newline_obj);
        if (newline == NULL || validate_newline(newline) < 0) {
            return NULL;
        }
    }

    line_buffering = convert_optional_bool(line_buffering_obj,
                                           self->line_buffering);
    if (line_buffering < 0) {
        return NULL;
    }
    write_through = convert_optional_bool(write_through_obj,
                                          self->write_through);
    if (write_through < 0) {
        return NULL;
    }

    if (_PyFile_Flush((PyObject *)self) < 0) {
        return NULL;
    }
    self->b2cratio = 0;

    if (newline_obj != NULL && set_newline(self, newline) < 0) {
        return NULL;
    }

    if (textiowrapper_change_encoding(
            self, encoding, errors, newline_obj != NULL) < 0) {
        return NULL;
    }

    self->line_buffering = line_buffering;
    self->write_through = write_through;
    Py_RETURN_NONE;
}

static int
textiowrapper_clear(PyObject *op)
{
    textio *self = textio_CAST(op);
    self->ok = 0;
    Py_CLEAR(self->buffer);
    Py_CLEAR(self->encoding);
    Py_CLEAR(self->encoder);
    Py_CLEAR(self->decoder);
    Py_CLEAR(self->readnl);
    Py_CLEAR(self->decoded_chars);
    Py_CLEAR(self->pending_bytes);
    Py_CLEAR(self->snapshot);
    Py_CLEAR(self->errors);
    Py_CLEAR(self->raw);

    Py_CLEAR(self->dict);
    return 0;
}

static void
textiowrapper_dealloc(PyObject *op)
{
    textio *self = textio_CAST(op);
    PyTypeObject *tp = Py_TYPE(self);
    self->finalizing = 1;
    if (_PyIOBase_finalize(op) < 0)
        return;
    self->ok = 0;
    _PyObject_GC_UNTRACK(self);
    FT_CLEAR_WEAKREFS(op, self->weakreflist);
    (void)textiowrapper_clear(op);
    tp->tp_free(self);
    Py_DECREF(tp);
}

static int
textiowrapper_traverse(PyObject *op, visitproc visit, void *arg)
{
    textio *self = textio_CAST(op);
    Py_VISIT(Py_TYPE(self));
    Py_VISIT(self->buffer);
    Py_VISIT(self->encoding);
    Py_VISIT(self->encoder);
    Py_VISIT(self->decoder);
    Py_VISIT(self->readnl);
    Py_VISIT(self->decoded_chars);
    Py_VISIT(self->pending_bytes);
    Py_VISIT(self->snapshot);
    Py_VISIT(self->errors);
    Py_VISIT(self->raw);

    Py_VISIT(self->dict);
    return 0;
}

static PyObject *
_io_TextIOWrapper_closed_get_impl(textio *self);

/* This macro takes some shortcuts to make the common case faster. */
#define CHECK_CLOSED(self) \
    do { \
        int r; \
        PyObject *_res; \
        if (Py_IS_TYPE(self, self->state->PyTextIOWrapper_Type)) { \
            if (self->raw != NULL) \
                r = _PyFileIO_closed(self->raw); \
            else { \
                _res = _io_TextIOWrapper_closed_get_impl(self); \
                if (_res == NULL) \
                    return NULL; \
                r = PyObject_IsTrue(_res); \
                Py_DECREF(_res); \
                if (r < 0) \
                    return NULL; \
            } \
            if (r > 0) { \
                PyErr_SetString(PyExc_ValueError, \
                                "I/O operation on closed file."); \
                return NULL; \
            } \
        } \
        else if (_PyIOBase_check_closed((PyObject *)self, Py_True) == NULL) \
            return NULL; \
    } while (0)

#define CHECK_INITIALIZED(self) \
    if (self->ok <= 0) { \
        PyErr_SetString(PyExc_ValueError, \
            "I/O operation on uninitialized object"); \
        return NULL; \
    }

#define CHECK_ATTACHED(self) \
    CHECK_INITIALIZED(self); \
    if (self->detached) { \
        PyErr_SetString(PyExc_ValueError, \
             "underlying buffer has been detached"); \
        return NULL; \
    }

#define CHECK_ATTACHED_INT(self) \
    if (self->ok <= 0) { \
        PyErr_SetString(PyExc_ValueError, \
            "I/O operation on uninitialized object"); \
        return -1; \
    } else if (self->detached) { \
        PyErr_SetString(PyExc_ValueError, \
             "underlying buffer has been detached"); \
        return -1; \
    }


/*[clinic input]
@critical_section
_io.TextIOWrapper.detach
[clinic start generated code]*/

static PyObject *
_io_TextIOWrapper_detach_impl(textio *self)
/*[clinic end generated code: output=7ba3715cd032d5f2 input=c908a3b4ef203b0f]*/
{
    PyObject *buffer;
    CHECK_ATTACHED(self);
    if (_PyFile_Flush((PyObject *)self) < 0) {
        return NULL;
    }
    buffer = self->buffer;
    self->buffer = NULL;
    self->detached = 1;
    return buffer;
}

/* Flush the internal write buffer. This doesn't explicitly flush the
   underlying buffered object, though. */
static int
_textiowrapper_writeflush(textio *self)
{
    _Py_CRITICAL_SECTION_ASSERT_OBJECT_LOCKED(self);

    if (self->pending_bytes == NULL)
        return 0;

    PyObject *pending = self->pending_bytes;
    PyObject *b;

    if (PyBytes_Check(pending)) {
        b = Py_NewRef(pending);
    }
    else if (PyUnicode_Check(pending)) {
        assert(PyUnicode_IS_ASCII(pending));
        assert(PyUnicode_GET_LENGTH(pending) == self->pending_bytes_count);
        b = PyBytes_FromStringAndSize(
                PyUnicode_DATA(pending), PyUnicode_GET_LENGTH(pending));
        if (b == NULL) {
            return -1;
        }
    }
    else {
        assert(PyList_Check(pending));
        b = PyBytes_FromStringAndSize(NULL, self->pending_bytes_count);
        if (b == NULL) {
            return -1;
        }

        char *buf = PyBytes_AsString(b);
        Py_ssize_t pos = 0;

        for (Py_ssize_t i = 0; i < PyList_GET_SIZE(pending); i++) {
            PyObject *obj = PyList_GET_ITEM(pending, i);
            char *src;
            Py_ssize_t len;
            if (PyUnicode_Check(obj)) {
                assert(PyUnicode_IS_ASCII(obj));
                src = PyUnicode_DATA(obj);
                len = PyUnicode_GET_LENGTH(obj);
            }
            else {
                assert(PyBytes_Check(obj));
                if (PyBytes_AsStringAndSize(obj, &src, &len) < 0) {
                    Py_DECREF(b);
                    return -1;
                }
            }
            memcpy(buf + pos, src, len);
            pos += len;
        }
        assert(pos == self->pending_bytes_count);
    }

    self->pending_bytes_count = 0;
    self->pending_bytes = NULL;
    Py_DECREF(pending);

    PyObject *ret;
    do {
        ret = PyObject_CallMethodOneArg(self->buffer, &_Py_ID(write), b);
    } while (ret == NULL && _PyIO_trap_eintr());
    Py_DECREF(b);
    // NOTE: We cleared buffer but we don't know how many bytes are actually written
    // when an error occurred.
    if (ret == NULL)
        return -1;
    Py_DECREF(ret);
    return 0;
}

/*[clinic input]
@critical_section
_io.TextIOWrapper.write
    text: unicode
    /
[clinic start generated code]*/

static PyObject *
_io_TextIOWrapper_write_impl(textio *self, PyObject *text)
/*[clinic end generated code: output=d2deb0d50771fcec input=73ec95c5c4a3489c]*/
{
    PyObject *ret;
    PyObject *b;
    Py_ssize_t textlen;
    int haslf = 0;
    int needflush = 0, text_needflush = 0;

    CHECK_ATTACHED(self);
    CHECK_CLOSED(self);

    if (self->encoder == NULL) {
        return _unsupported(self->state, "not writable");
    }

    Py_INCREF(text);

    textlen = PyUnicode_GET_LENGTH(text);

    if ((self->writetranslate && self->writenl != NULL) || self->line_buffering)
        if (PyUnicode_FindChar(text, '\n', 0, PyUnicode_GET_LENGTH(text), 1) != -1)
            haslf = 1;

    if (haslf && self->writetranslate && self->writenl != NULL) {
        PyObject *newtext = _PyObject_CallMethod(text, &_Py_ID(replace),
                                                 "ss", "\n", self->writenl);
        Py_DECREF(text);
        if (newtext == NULL)
            return NULL;
        text = newtext;
    }

    if (self->write_through)
        text_needflush = 1;
    if (self->line_buffering &&
        (haslf ||
         PyUnicode_FindChar(text, '\r', 0, PyUnicode_GET_LENGTH(text), 1) != -1))
        needflush = 1;

    /* XXX What if we were just reading? */
    if (self->encodefunc != NULL) {
        if (PyUnicode_IS_ASCII(text) &&
                // See bpo-43260
                PyUnicode_GET_LENGTH(text) <= self->chunk_size &&
                is_asciicompat_encoding(self->encodefunc)) {
            b = Py_NewRef(text);
        }
        else {
            b = (*self->encodefunc)((PyObject *) self, text);
        }
        self->encoding_start_of_stream = 0;
    }
    else {
        b = PyObject_CallMethodOneArg(self->encoder, &_Py_ID(encode), text);
    }

    Py_DECREF(text);
    if (b == NULL)
        return NULL;
    if (b != text && !PyBytes_Check(b)) {
        PyErr_Format(PyExc_TypeError,
                     "encoder should return a bytes object, not '%.200s'",
                     Py_TYPE(b)->tp_name);
        Py_DECREF(b);
        return NULL;
    }

    Py_ssize_t bytes_len;
    if (b == text) {
        bytes_len = PyUnicode_GET_LENGTH(b);
    }
    else {
        bytes_len = PyBytes_GET_SIZE(b);
    }

    // We should avoid concatenating huge data.
    // Flush the buffer before adding b to the buffer if b is not small.
    // https://github.com/python/cpython/issues/87426
    if (bytes_len >= self->chunk_size) {
        // _textiowrapper_writeflush() calls buffer.write().
        // self->pending_bytes can be appended during buffer->write()
        // or other thread.
        // We need to loop until buffer becomes empty.
        // https://github.com/python/cpython/issues/118138
        // https://github.com/python/cpython/issues/119506
        while (self->pending_bytes != NULL) {
            if (_textiowrapper_writeflush(self) < 0) {
                Py_DECREF(b);
                return NULL;
            }
        }
    }

    if (self->pending_bytes == NULL) {
        assert(self->pending_bytes_count == 0);
        self->pending_bytes = b;
    }
    else if (!PyList_CheckExact(self->pending_bytes)) {
        PyObject *list = PyList_New(2);
        if (list == NULL) {
            Py_DECREF(b);
            return NULL;
        }
        // Since Python 3.12, allocating GC object won't trigger GC and release
        // GIL. See https://github.com/python/cpython/issues/97922
        assert(!PyList_CheckExact(self->pending_bytes));
        PyList_SET_ITEM(list, 0, self->pending_bytes);
        PyList_SET_ITEM(list, 1, b);
        self->pending_bytes = list;
    }
    else {
        if (PyList_Append(self->pending_bytes, b) < 0) {
            Py_DECREF(b);
            return NULL;
        }
        Py_DECREF(b);
    }

    self->pending_bytes_count += bytes_len;
    if (self->pending_bytes_count >= self->chunk_size || needflush ||
        text_needflush) {
        if (_textiowrapper_writeflush(self) < 0)
            return NULL;
    }

    if (needflush) {
        if (_PyFile_Flush(self->buffer) < 0) {
            return NULL;
        }
    }

    if (self->snapshot != NULL) {
        textiowrapper_set_decoded_chars(self, NULL);
        Py_CLEAR(self->snapshot);
    }

    if (self->decoder) {
        ret = PyObject_CallMethodNoArgs(self->decoder, &_Py_ID(reset));
        if (ret == NULL)
            return NULL;
        Py_DECREF(ret);
    }

    return PyLong_FromSsize_t(textlen);
}

/* Steal a reference to chars and store it in the decoded_char buffer;
 */
static void
textiowrapper_set_decoded_chars(textio *self, PyObject *chars)
{
    Py_XSETREF(self->decoded_chars, chars);
    self->decoded_chars_used = 0;
}

static PyObject *
textiowrapper_get_decoded_chars(textio *self, Py_ssize_t n)
{
    PyObject *chars;
    Py_ssize_t avail;

    if (self->decoded_chars == NULL)
        return Py_GetConstant(Py_CONSTANT_EMPTY_STR);

    avail = (PyUnicode_GET_LENGTH(self->decoded_chars)
             - self->decoded_chars_used);

    assert(avail >= 0);

    if (n < 0 || n > avail)
        n = avail;

    if (self->decoded_chars_used > 0 || n < avail) {
        chars = PyUnicode_Substring(self->decoded_chars,
                                    self->decoded_chars_used,
                                    self->decoded_chars_used + n);
        if (chars == NULL)
            return NULL;
    }
    else {
        chars = Py_NewRef(self->decoded_chars);
    }

    self->decoded_chars_used += n;
    return chars;
}

/* Read and decode the next chunk of data from the BufferedReader.
 */
static int
textiowrapper_read_chunk(textio *self, Py_ssize_t size_hint)
{
    PyObject *dec_buffer = NULL;
    PyObject *dec_flags = NULL;
    PyObject *input_chunk = NULL;
    Py_buffer input_chunk_buf;
    PyObject *decoded_chars, *chunk_size;
    Py_ssize_t nbytes, nchars;
    int eof;

    /* The return value is True unless EOF was reached.  The decoded string is
     * placed in self._decoded_chars (replacing its previous value).  The
     * entire input chunk is sent to the decoder, though some of it may remain
     * buffered in the decoder, yet to be converted.
     */

    if (self->decoder == NULL) {
        _unsupported(self->state, "not readable");
        return -1;
    }

    if (self->telling) {
        /* To prepare for tell(), we need to snapshot a point in the file
         * where the decoder's input buffer is empty.
         */
        PyObject *state = PyObject_CallMethodNoArgs(self->decoder,
                                                     &_Py_ID(getstate));
        if (state == NULL)
            return -1;
        /* Given this, we know there was a valid snapshot point
         * len(dec_buffer) bytes ago with decoder state (b'', dec_flags).
         */
        if (!PyTuple_Check(state)) {
            PyErr_SetString(PyExc_TypeError,
                            "illegal decoder state");
            Py_DECREF(state);
            return -1;
        }
        if (!PyArg_ParseTuple(state,
                              "OO;illegal decoder state", &dec_buffer, &dec_flags))
        {
            Py_DECREF(state);
            return -1;
        }

        if (!PyBytes_Check(dec_buffer)) {
            PyErr_Format(PyExc_TypeError,
                         "illegal decoder state: the first item should be a "
                         "bytes object, not '%.200s'",
                         Py_TYPE(dec_buffer)->tp_name);
            Py_DECREF(state);
            return -1;
        }
        Py_INCREF(dec_buffer);
        Py_INCREF(dec_flags);
        Py_DECREF(state);
    }

    /* Read a chunk, decode it, and put the result in self._decoded_chars. */
    if (size_hint > 0) {
        size_hint = (Py_ssize_t)(Py_MAX(self->b2cratio, 1.0) * size_hint);
    }
    chunk_size = PyLong_FromSsize_t(Py_MAX(self->chunk_size, size_hint));
    if (chunk_size == NULL)
        goto fail;

    input_chunk = PyObject_CallMethodOneArg(self->buffer,
        (self->has_read1 ? &_Py_ID(read1): &_Py_ID(read)),
        chunk_size);
    Py_DECREF(chunk_size);
    if (input_chunk == NULL)
        goto fail;

    if (PyObject_GetBuffer(input_chunk, &input_chunk_buf, 0) != 0) {
        PyErr_Format(PyExc_TypeError,
                     "underlying %s() should have returned a bytes-like object, "
                     "not '%.200s'", (self->has_read1 ? "read1": "read"),
                     Py_TYPE(input_chunk)->tp_name);
        goto fail;
    }

    nbytes = input_chunk_buf.len;
    eof = (nbytes == 0);

    decoded_chars = _textiowrapper_decode(self->state, self->decoder,
                                          input_chunk, eof);
    PyBuffer_Release(&input_chunk_buf);
    if (decoded_chars == NULL)
        goto fail;

    textiowrapper_set_decoded_chars(self, decoded_chars);
    nchars = PyUnicode_GET_LENGTH(decoded_chars);
    if (nchars > 0)
        self->b2cratio = (double) nbytes / nchars;
    else
        self->b2cratio = 0.0;
    if (nchars > 0)
        eof = 0;

    if (self->telling) {
        /* At the snapshot point, len(dec_buffer) bytes before the read, the
         * next input to be decoded is dec_buffer + input_chunk.
         */
        PyObject *next_input = dec_buffer;
        PyBytes_Concat(&next_input, input_chunk);
        dec_buffer = NULL; /* Reference lost to PyBytes_Concat */
        if (next_input == NULL) {
            goto fail;
        }
        PyObject *snapshot = Py_BuildValue("NN", dec_flags, next_input);
        if (snapshot == NULL) {
            dec_flags = NULL;
            goto fail;
        }
        Py_XSETREF(self->snapshot, snapshot);
    }
    Py_DECREF(input_chunk);

    return (eof == 0);

  fail:
    Py_XDECREF(dec_buffer);
    Py_XDECREF(dec_flags);
    Py_XDECREF(input_chunk);
    return -1;
}

/*[clinic input]
@critical_section
_io.TextIOWrapper.read
    size as n: Py_ssize_t(accept={int, NoneType}) = -1
    /
[clinic start generated code]*/

static PyObject *
_io_TextIOWrapper_read_impl(textio *self, Py_ssize_t n)
/*[clinic end generated code: output=7e651ce6cc6a25a6 input=67d14c5661121377]*/
{
    PyObject *result = NULL, *chunks = NULL;

    CHECK_ATTACHED(self);
    CHECK_CLOSED(self);

    if (self->decoder == NULL) {
        return _unsupported(self->state, "not readable");
    }

    if (_textiowrapper_writeflush(self) < 0)
        return NULL;

    if (n < 0) {
        /* Read everything */
        PyObject *bytes = PyObject_CallMethodNoArgs(self->buffer, &_Py_ID(read));
        PyObject *decoded;
        if (bytes == NULL)
            goto fail;

        if (bytes == Py_None){
            Py_DECREF(bytes);
            PyErr_SetString(PyExc_BlockingIOError, "Read returned None.");
            return NULL;
        }

        _PyIO_State *state = self->state;
        if (Py_IS_TYPE(self->decoder, state->PyIncrementalNewlineDecoder_Type))
            decoded = _PyIncrementalNewlineDecoder_decode(self->decoder,
                                                          bytes, 1);
        else
            decoded = PyObject_CallMethodObjArgs(
                self->decoder, &_Py_ID(decode), bytes, Py_True, NULL);
        Py_DECREF(bytes);
        if (check_decoded(decoded) < 0)
            goto fail;

        result = textiowrapper_get_decoded_chars(self, -1);

        if (result == NULL) {
            Py_DECREF(decoded);
            return NULL;
        }

        PyUnicode_AppendAndDel(&result, decoded);
        if (result == NULL)
            goto fail;

        if (self->snapshot != NULL) {
            textiowrapper_set_decoded_chars(self, NULL);
            Py_CLEAR(self->snapshot);
        }
        return result;
    }
    else {
        int res = 1;
        Py_ssize_t remaining = n;

        result = textiowrapper_get_decoded_chars(self, n);
        if (result == NULL)
            goto fail;
        remaining -= PyUnicode_GET_LENGTH(result);

        /* Keep reading chunks until we have n characters to return */
        while (remaining > 0) {
            res = textiowrapper_read_chunk(self, remaining);
            if (res < 0) {
                /* NOTE: PyErr_SetFromErrno() calls PyErr_CheckSignals()
                   when EINTR occurs so we needn't do it ourselves. */
                if (_PyIO_trap_eintr()) {
                    continue;
                }
                goto fail;
            }
            if (res == 0)  /* EOF */
                break;
            if (chunks == NULL) {
                chunks = PyList_New(0);
                if (chunks == NULL)
                    goto fail;
            }
            if (PyUnicode_GET_LENGTH(result) > 0 &&
                PyList_Append(chunks, result) < 0)
                goto fail;
            Py_DECREF(result);
            result = textiowrapper_get_decoded_chars(self, remaining);
            if (result == NULL)
                goto fail;
            remaining -= PyUnicode_GET_LENGTH(result);
        }
        if (chunks != NULL) {
            if (result != NULL && PyList_Append(chunks, result) < 0)
                goto fail;
            _Py_DECLARE_STR(empty, "");
            Py_XSETREF(result, PyUnicode_Join(&_Py_STR(empty), chunks));
            if (result == NULL)
                goto fail;
            Py_CLEAR(chunks);
        }
        return result;
    }
  fail:
    Py_XDECREF(result);
    Py_XDECREF(chunks);
    return NULL;
}


/* NOTE: `end` must point to the real end of the Py_UCS4 storage,
   that is to the NUL character. Otherwise the function will produce
   incorrect results. */
static const char *
find_control_char(int kind, const char *s, const char *end, Py_UCS4 ch)
{
    if (kind == PyUnicode_1BYTE_KIND) {
        assert(ch < 256);
        return (char *) memchr((const void *) s, (char) ch, end - s);
    }
    for (;;) {
        while (PyUnicode_READ(kind, s, 0) > ch)
            s += kind;
        if (PyUnicode_READ(kind, s, 0) == ch)
            return s;
        if (s == end)
            return NULL;
        s += kind;
    }
}

Py_ssize_t
_PyIO_find_line_ending(
    int translated, int universal, PyObject *readnl,
    int kind, const char *start, const char *end, Py_ssize_t *consumed)
{
    Py_ssize_t len = (end - start)/kind;

    if (translated) {
        /* Newlines are already translated, only search for \n */
        const char *pos = find_control_char(kind, start, end, '\n');
        if (pos != NULL)
            return (pos - start)/kind + 1;
        else {
            *consumed = len;
            return -1;
        }
    }
    else if (universal) {
        /* Universal newline search. Find any of \r, \r\n, \n
         * The decoder ensures that \r\n are not split in two pieces
         */
        const char *s = start;
        for (;;) {
            Py_UCS4 ch;
            /* Fast path for non-control chars. The loop always ends
               since the Unicode string is NUL-terminated. */
            while (PyUnicode_READ(kind, s, 0) > '\r')
                s += kind;
            if (s >= end) {
                *consumed = len;
                return -1;
            }
            ch = PyUnicode_READ(kind, s, 0);
            s += kind;
            if (ch == '\n')
                return (s - start)/kind;
            if (ch == '\r') {
                if (PyUnicode_READ(kind, s, 0) == '\n')
                    return (s - start)/kind + 1;
                else
                    return (s - start)/kind;
            }
        }
    }
    else {
        /* Non-universal mode. */
        Py_ssize_t readnl_len = PyUnicode_GET_LENGTH(readnl);
        const Py_UCS1 *nl = PyUnicode_1BYTE_DATA(readnl);
        /* Assume that readnl is an ASCII character. */
        assert(PyUnicode_KIND(readnl) == PyUnicode_1BYTE_KIND);
        if (readnl_len == 1) {
            const char *pos = find_control_char(kind, start, end, nl[0]);
            if (pos != NULL)
                return (pos - start)/kind + 1;
            *consumed = len;
            return -1;
        }
        else {
            const char *s = start;
            const char *e = end - (readnl_len - 1)*kind;
            const char *pos;
            if (e < s)
                e = s;
            while (s < e) {
                Py_ssize_t i;
                const char *pos = find_control_char(kind, s, end, nl[0]);
                if (pos == NULL || pos >= e)
                    break;
                for (i = 1; i < readnl_len; i++) {
                    if (PyUnicode_READ(kind, pos, i) != nl[i])
                        break;
                }
                if (i == readnl_len)
                    return (pos - start)/kind + readnl_len;
                s = pos + kind;
            }
            pos = find_control_char(kind, e, end, nl[0]);
            if (pos == NULL)
                *consumed = len;
            else
                *consumed = (pos - start)/kind;
            return -1;
        }
    }
}

static PyObject *
_textiowrapper_readline(textio *self, Py_ssize_t limit)
{
    PyObject *line = NULL, *chunks = NULL, *remaining = NULL;
    Py_ssize_t start, endpos, chunked, offset_to_buffer;
    int res;

    CHECK_CLOSED(self);

    if (_textiowrapper_writeflush(self) < 0)
        return NULL;

    chunked = 0;

    while (1) {
        const char *ptr;
        Py_ssize_t line_len;
        int kind;
        Py_ssize_t consumed = 0;

        /* First, get some data if necessary */
        res = 1;
        while (!self->decoded_chars ||
               !PyUnicode_GET_LENGTH(self->decoded_chars)) {
            res = textiowrapper_read_chunk(self, 0);
            if (res < 0) {
                /* NOTE: PyErr_SetFromErrno() calls PyErr_CheckSignals()
                   when EINTR occurs so we needn't do it ourselves. */
                if (_PyIO_trap_eintr()) {
                    continue;
                }
                goto error;
            }
            if (res == 0)
                break;
        }
        if (res == 0) {
            /* end of file */
            textiowrapper_set_decoded_chars(self, NULL);
            Py_CLEAR(self->snapshot);
            start = endpos = offset_to_buffer = 0;
            break;
        }

        if (remaining == NULL) {
            line = Py_NewRef(self->decoded_chars);
            start = self->decoded_chars_used;
            offset_to_buffer = 0;
        }
        else {
            assert(self->decoded_chars_used == 0);
            line = PyUnicode_Concat(remaining, self->decoded_chars);
            start = 0;
            offset_to_buffer = PyUnicode_GET_LENGTH(remaining);
            Py_CLEAR(remaining);
            if (line == NULL)
                goto error;
        }

        ptr = PyUnicode_DATA(line);
        line_len = PyUnicode_GET_LENGTH(line);
        kind = PyUnicode_KIND(line);

        endpos = _PyIO_find_line_ending(
            self->readtranslate, self->readuniversal, self->readnl,
            kind,
            ptr + kind * start,
            ptr + kind * line_len,
            &consumed);
        if (endpos >= 0) {
            endpos += start;
            if (limit >= 0 && (endpos - start) + chunked >= limit)
                endpos = start + limit - chunked;
            break;
        }

        /* We can put aside up to `endpos` */
        endpos = consumed + start;
        if (limit >= 0 && (endpos - start) + chunked >= limit) {
            /* Didn't find line ending, but reached length limit */
            endpos = start + limit - chunked;
            break;
        }

        if (endpos > start) {
            /* No line ending seen yet - put aside current data */
            PyObject *s;
            if (chunks == NULL) {
                chunks = PyList_New(0);
                if (chunks == NULL)
                    goto error;
            }
            s = PyUnicode_Substring(line, start, endpos);
            if (s == NULL)
                goto error;
            if (PyList_Append(chunks, s) < 0) {
                Py_DECREF(s);
                goto error;
            }
            chunked += PyUnicode_GET_LENGTH(s);
            Py_DECREF(s);
        }
        /* There may be some remaining bytes we'll have to prepend to the
           next chunk of data */
        if (endpos < line_len) {
            remaining = PyUnicode_Substring(line, endpos, line_len);
            if (remaining == NULL)
                goto error;
        }
        Py_CLEAR(line);
        /* We have consumed the buffer */
        textiowrapper_set_decoded_chars(self, NULL);
    }

    if (line != NULL) {
        /* Our line ends in the current buffer */
        self->decoded_chars_used = endpos - offset_to_buffer;
        if (start > 0 || endpos < PyUnicode_GET_LENGTH(line)) {
            PyObject *s = PyUnicode_Substring(line, start, endpos);
            Py_CLEAR(line);
            if (s == NULL)
                goto error;
            line = s;
        }
    }
    if (remaining != NULL) {
        if (chunks == NULL) {
            chunks = PyList_New(0);
            if (chunks == NULL)
                goto error;
        }
        if (PyList_Append(chunks, remaining) < 0)
            goto error;
        Py_CLEAR(remaining);
    }
    if (chunks != NULL) {
        if (line != NULL) {
            if (PyList_Append(chunks, line) < 0)
                goto error;
            Py_DECREF(line);
        }
        line = PyUnicode_Join(&_Py_STR(empty), chunks);
        if (line == NULL)
            goto error;
        Py_CLEAR(chunks);
    }
    if (line == NULL) {
        line = &_Py_STR(empty);
    }

    return line;

  error:
    Py_XDECREF(chunks);
    Py_XDECREF(remaining);
    Py_XDECREF(line);
    return NULL;
}

/*[clinic input]
@critical_section
_io.TextIOWrapper.readline
    size: Py_ssize_t = -1
    /
[clinic start generated code]*/

static PyObject *
_io_TextIOWrapper_readline_impl(textio *self, Py_ssize_t size)
/*[clinic end generated code: output=344afa98804e8b25 input=b65bab871dc3ddba]*/
{
    CHECK_ATTACHED(self);
    return _textiowrapper_readline(self, size);
}

/* Seek and Tell */

typedef struct {
    Py_off_t start_pos;
    int dec_flags;
    int bytes_to_feed;
    int chars_to_skip;
    char need_eof;
} cookie_type;

/*
   To speed up cookie packing/unpacking, we store the fields in a temporary
   string and call _PyLong_FromByteArray() or _PyLong_AsByteArray (resp.).
   The following macros define at which offsets in the intermediary byte
   string the various CookieStruct fields will be stored.
 */

#define COOKIE_BUF_LEN      (sizeof(Py_off_t) + 3 * sizeof(int) + sizeof(char))

#if PY_BIG_ENDIAN
/* We want the least significant byte of start_pos to also be the least
   significant byte of the cookie, which means that in big-endian mode we
   must copy the fields in reverse order. */

# define OFF_START_POS      (sizeof(char) + 3 * sizeof(int))
# define OFF_DEC_FLAGS      (sizeof(char) + 2 * sizeof(int))
# define OFF_BYTES_TO_FEED  (sizeof(char) + sizeof(int))
# define OFF_CHARS_TO_SKIP  (sizeof(char))
# define OFF_NEED_EOF       0

#else
/* Little-endian mode: the least significant byte of start_pos will
   naturally end up the least significant byte of the cookie. */

# define OFF_START_POS      0
# define OFF_DEC_FLAGS      (sizeof(Py_off_t))
# define OFF_BYTES_TO_FEED  (sizeof(Py_off_t) + sizeof(int))
# define OFF_CHARS_TO_SKIP  (sizeof(Py_off_t) + 2 * sizeof(int))
# define OFF_NEED_EOF       (sizeof(Py_off_t) + 3 * sizeof(int))

#endif

static int
textiowrapper_parse_cookie(cookie_type *cookie, PyObject *cookieObj)
{
    unsigned char buffer[COOKIE_BUF_LEN];
    PyLongObject *cookieLong = (PyLongObject *)PyNumber_Long(cookieObj);
    if (cookieLong == NULL)
        return -1;

    if (_PyLong_AsByteArray(cookieLong, buffer, sizeof(buffer),
                            PY_LITTLE_ENDIAN, 0, 1) < 0) {
        Py_DECREF(cookieLong);
        return -1;
    }
    Py_DECREF(cookieLong);

    memcpy(&cookie->start_pos, buffer + OFF_START_POS, sizeof(cookie->start_pos));
    memcpy(&cookie->dec_flags, buffer + OFF_DEC_FLAGS, sizeof(cookie->dec_flags));
    memcpy(&cookie->bytes_to_feed, buffer + OFF_BYTES_TO_FEED, sizeof(cookie->bytes_to_feed));
    memcpy(&cookie->chars_to_skip, buffer + OFF_CHARS_TO_SKIP, sizeof(cookie->chars_to_skip));
    memcpy(&cookie->need_eof, buffer + OFF_NEED_EOF, sizeof(cookie->need_eof));

    return 0;
}

static PyObject *
textiowrapper_build_cookie(cookie_type *cookie)
{
    unsigned char buffer[COOKIE_BUF_LEN];

    memcpy(buffer + OFF_START_POS, &cookie->start_pos, sizeof(cookie->start_pos));
    memcpy(buffer + OFF_DEC_FLAGS, &cookie->dec_flags, sizeof(cookie->dec_flags));
    memcpy(buffer + OFF_BYTES_TO_FEED, &cookie->bytes_to_feed, sizeof(cookie->bytes_to_feed));
    memcpy(buffer + OFF_CHARS_TO_SKIP, &cookie->chars_to_skip, sizeof(cookie->chars_to_skip));
    memcpy(buffer + OFF_NEED_EOF, &cookie->need_eof, sizeof(cookie->need_eof));

    return _PyLong_FromByteArray(buffer, sizeof(buffer),
                                 PY_LITTLE_ENDIAN, 0);
}

static int
_textiowrapper_decoder_setstate(textio *self, cookie_type *cookie)
{
    PyObject *res;
    /* When seeking to the start of the stream, we call decoder.reset()
       rather than decoder.getstate().
       This is for a few decoders such as utf-16 for which the state value
       at start is not (b"", 0) but e.g. (b"", 2) (meaning, in the case of
       utf-16, that we are expecting a BOM).
    */
    if (cookie->start_pos == 0 && cookie->dec_flags == 0) {
        res = PyObject_CallMethodNoArgs(self->decoder, &_Py_ID(reset));
    }
    else {
        res = _PyObject_CallMethod(self->decoder, &_Py_ID(setstate),
                                   "((yi))", "", cookie->dec_flags);
    }
    if (res == NULL) {
        return -1;
    }
    Py_DECREF(res);
    return 0;
}

static int
_textiowrapper_encoder_reset(textio *self, int start_of_stream)
{
    PyObject *res;
    if (start_of_stream) {
        res = PyObject_CallMethodNoArgs(self->encoder, &_Py_ID(reset));
        self->encoding_start_of_stream = 1;
    }
    else {
        res = PyObject_CallMethodOneArg(self->encoder, &_Py_ID(setstate),
                                        _PyLong_GetZero());
        self->encoding_start_of_stream = 0;
    }
    if (res == NULL)
        return -1;
    Py_DECREF(res);
    return 0;
}

static int
_textiowrapper_encoder_setstate(textio *self, cookie_type *cookie)
{
    /* Same as _textiowrapper_decoder_setstate() above. */
    return _textiowrapper_encoder_reset(
        self, cookie->start_pos == 0 && cookie->dec_flags == 0);
}

/*[clinic input]
@critical_section
_io.TextIOWrapper.seek
    cookie as cookieObj: object
      Zero or an opaque number returned by tell().
    whence: int(c_default='0') = os.SEEK_SET
      The relative position to seek from.
    /

Set the stream position, and return the new stream position.

Four operations are supported, given by the following argument
combinations:

- seek(0, SEEK_SET): Rewind to the start of the stream.
- seek(cookie, SEEK_SET): Restore a previous position;
  'cookie' must be a number returned by tell().
- seek(0, SEEK_END): Fast-forward to the end of the stream.
- seek(0, SEEK_CUR): Leave the current stream position unchanged.

Any other argument combinations are invalid,
and may raise exceptions.
[clinic start generated code]*/

static PyObject *
_io_TextIOWrapper_seek_impl(textio *self, PyObject *cookieObj, int whence)
/*[clinic end generated code: output=0a15679764e2d04d input=4bea78698be23d7e]*/
{
    PyObject *posobj;
    cookie_type cookie;
    PyObject *res;
    int cmp;
    PyObject *snapshot;

    CHECK_ATTACHED(self);
    CHECK_CLOSED(self);

    Py_INCREF(cookieObj);

    if (!self->seekable) {
        _unsupported(self->state, "underlying stream is not seekable");
        goto fail;
    }

    PyObject *zero = _PyLong_GetZero();  // borrowed reference

    switch (whence) {
    case SEEK_CUR:
        /* seek relative to current position */
        cmp = PyObject_RichCompareBool(cookieObj, zero, Py_EQ);
        if (cmp < 0)
            goto fail;

        if (cmp == 0) {
            _unsupported(self->state, "can't do nonzero cur-relative seeks");
            goto fail;
        }

        /* Seeking to the current position should attempt to
         * sync the underlying buffer with the current position.
         */
        Py_DECREF(cookieObj);
        cookieObj = PyObject_CallMethodNoArgs((PyObject *)self, &_Py_ID(tell));
        if (cookieObj == NULL)
            goto fail;
        break;

    case SEEK_END:
        /* seek relative to end of file */
        cmp = PyObject_RichCompareBool(cookieObj, zero, Py_EQ);
        if (cmp < 0)
            goto fail;

        if (cmp == 0) {
            _unsupported(self->state, "can't do nonzero end-relative seeks");
            goto fail;
        }

        if (_PyFile_Flush((PyObject *)self) < 0) {
            goto fail;
        }

        textiowrapper_set_decoded_chars(self, NULL);
        Py_CLEAR(self->snapshot);
        if (self->decoder) {
            res = PyObject_CallMethodNoArgs(self->decoder, &_Py_ID(reset));
            if (res == NULL)
                goto fail;
            Py_DECREF(res);
        }

        res = _PyObject_CallMethod(self->buffer, &_Py_ID(seek), "ii", 0, 2);
        Py_CLEAR(cookieObj);
        if (res == NULL)
            goto fail;
        if (self->encoder) {
            /* If seek() == 0, we are at the start of stream, otherwise not */
            cmp = PyObject_RichCompareBool(res, zero, Py_EQ);
            if (cmp < 0 || _textiowrapper_encoder_reset(self, cmp)) {
                Py_DECREF(res);
                goto fail;
            }
        }
        return res;

    case SEEK_SET:
        break;

    default:
        PyErr_Format(PyExc_ValueError,
                     "invalid whence (%d, should be %d, %d or %d)", whence,
                     SEEK_SET, SEEK_CUR, SEEK_END);
        goto fail;
    }

    cmp = PyObject_RichCompareBool(cookieObj, zero, Py_LT);
    if (cmp < 0)
        goto fail;

    if (cmp == 1) {
        PyErr_Format(PyExc_ValueError,
                     "negative seek position %R", cookieObj);
        goto fail;
    }

    if (_PyFile_Flush((PyObject *)self) < 0) {
        goto fail;
    }

    /* The strategy of seek() is to go back to the safe start point
     * and replay the effect of read(chars_to_skip) from there.
     */
    if (textiowrapper_parse_cookie(&cookie, cookieObj) < 0)
        goto fail;

    /* Seek back to the safe start point. */
    posobj = PyLong_FromOff_t(cookie.start_pos);
    if (posobj == NULL)
        goto fail;
    res = PyObject_CallMethodOneArg(self->buffer, &_Py_ID(seek), posobj);
    Py_DECREF(posobj);
    if (res == NULL)
        goto fail;
    Py_DECREF(res);

    textiowrapper_set_decoded_chars(self, NULL);
    Py_CLEAR(self->snapshot);

    /* Restore the decoder to its state from the safe start point. */
    if (self->decoder) {
        if (_textiowrapper_decoder_setstate(self, &cookie) < 0)
            goto fail;
    }

    if (cookie.chars_to_skip) {
        /* Just like _read_chunk, feed the decoder and save a snapshot. */
        PyObject *input_chunk = _PyObject_CallMethod(self->buffer, &_Py_ID(read),
                                                     "i", cookie.bytes_to_feed);
        PyObject *decoded;

        if (input_chunk == NULL)
            goto fail;

        if (!PyBytes_Check(input_chunk)) {
            PyErr_Format(PyExc_TypeError,
                         "underlying read() should have returned a bytes "
                         "object, not '%.200s'",
                         Py_TYPE(input_chunk)->tp_name);
            Py_DECREF(input_chunk);
            goto fail;
        }

        snapshot = Py_BuildValue("iN", cookie.dec_flags, input_chunk);
        if (snapshot == NULL) {
            goto fail;
        }
        Py_XSETREF(self->snapshot, snapshot);

        decoded = PyObject_CallMethodObjArgs(self->decoder, &_Py_ID(decode),
            input_chunk, cookie.need_eof ? Py_True : Py_False, NULL);

        if (check_decoded(decoded) < 0)
            goto fail;

        textiowrapper_set_decoded_chars(self, decoded);

        /* Skip chars_to_skip of the decoded characters. */
        if (PyUnicode_GetLength(self->decoded_chars) < cookie.chars_to_skip) {
            PyErr_SetString(PyExc_OSError, "can't restore logical file position");
            goto fail;
        }
        self->decoded_chars_used = cookie.chars_to_skip;
    }
    else {
        snapshot = Py_BuildValue("iy", cookie.dec_flags, "");
        if (snapshot == NULL)
            goto fail;
        Py_XSETREF(self->snapshot, snapshot);
    }

    /* Finally, reset the encoder (merely useful for proper BOM handling) */
    if (self->encoder) {
        if (_textiowrapper_encoder_setstate(self, &cookie) < 0)
            goto fail;
    }
    return cookieObj;
  fail:
    Py_XDECREF(cookieObj);
    return NULL;

}

/*[clinic input]
@critical_section
_io.TextIOWrapper.tell

Return the stream position as an opaque number.

The return value of tell() can be given as input to seek(), to restore a
previous stream position.
[clinic start generated code]*/

static PyObject *
_io_TextIOWrapper_tell_impl(textio *self)
/*[clinic end generated code: output=4f168c08bf34ad5f input=415d6b4e4f8e6e8c]*/
{
    PyObject *res;
    PyObject *posobj = NULL;
    cookie_type cookie = {0,0,0,0,0};
    PyObject *next_input;
    Py_ssize_t chars_to_skip, chars_decoded;
    Py_ssize_t skip_bytes, skip_back;
    PyObject *saved_state = NULL;
    const char *input, *input_end;
    Py_ssize_t dec_buffer_len;
    int dec_flags;

    CHECK_ATTACHED(self);
    CHECK_CLOSED(self);

    if (!self->seekable) {
        _unsupported(self->state, "underlying stream is not seekable");
        goto fail;
    }
    if (!self->telling) {
        PyErr_SetString(PyExc_OSError,
                        "telling position disabled by next() call");
        goto fail;
    }

    if (_textiowrapper_writeflush(self) < 0)
        return NULL;
    if (_PyFile_Flush((PyObject *)self) < 0) {
        goto fail;
    }

    posobj = PyObject_CallMethodNoArgs(self->buffer, &_Py_ID(tell));
    if (posobj == NULL)
        goto fail;

    if (self->decoder == NULL || self->snapshot == NULL) {
        assert (self->decoded_chars == NULL || PyUnicode_GetLength(self->decoded_chars) == 0);
        return posobj;
    }

#if defined(HAVE_LARGEFILE_SUPPORT)
    cookie.start_pos = PyLong_AsLongLong(posobj);
#else
    cookie.start_pos = PyLong_AsLong(posobj);
#endif
    Py_DECREF(posobj);
    if (PyErr_Occurred())
        goto fail;

    /* Skip backward to the snapshot point (see _read_chunk). */
    assert(PyTuple_Check(self->snapshot));
    if (!PyArg_ParseTuple(self->snapshot, "iO", &cookie.dec_flags, &next_input))
        goto fail;

    assert (PyBytes_Check(next_input));

    cookie.start_pos -= PyBytes_GET_SIZE(next_input);

    /* How many decoded characters have been used up since the snapshot? */
    if (self->decoded_chars_used == 0)  {
        /* We haven't moved from the snapshot point. */
        return textiowrapper_build_cookie(&cookie);
    }

    chars_to_skip = self->decoded_chars_used;

    /* Decoder state will be restored at the end */
    saved_state = PyObject_CallMethodNoArgs(self->decoder,
                                             &_Py_ID(getstate));
    if (saved_state == NULL)
        goto fail;

#define DECODER_GETSTATE() do { \
        PyObject *dec_buffer; \
        PyObject *_state = PyObject_CallMethodNoArgs(self->decoder, \
            &_Py_ID(getstate)); \
        if (_state == NULL) \
            goto fail; \
        if (!PyTuple_Check(_state)) { \
            PyErr_SetString(PyExc_TypeError, \
                            "illegal decoder state"); \
            Py_DECREF(_state); \
            goto fail; \
        } \
        if (!PyArg_ParseTuple(_state, "Oi;illegal decoder state", \
                              &dec_buffer, &dec_flags)) \
        { \
            Py_DECREF(_state); \
            goto fail; \
        } \
        if (!PyBytes_Check(dec_buffer)) { \
            PyErr_Format(PyExc_TypeError, \
                         "illegal decoder state: the first item should be a " \
                         "bytes object, not '%.200s'", \
                         Py_TYPE(dec_buffer)->tp_name); \
            Py_DECREF(_state); \
            goto fail; \
        } \
        dec_buffer_len = PyBytes_GET_SIZE(dec_buffer); \
        Py_DECREF(_state); \
    } while (0)

#define DECODER_DECODE(start, len, res) do { \
        PyObject *_decoded = _PyObject_CallMethod( \
            self->decoder, &_Py_ID(decode), "y#", start, len); \
        if (check_decoded(_decoded) < 0) \
            goto fail; \
        res = PyUnicode_GET_LENGTH(_decoded); \
        Py_DECREF(_decoded); \
    } while (0)

    /* Fast search for an acceptable start point, close to our
       current pos */
    skip_bytes = (Py_ssize_t) (self->b2cratio * chars_to_skip);
    skip_back = 1;
    assert(skip_back <= PyBytes_GET_SIZE(next_input));
    input = PyBytes_AS_STRING(next_input);
    while (skip_bytes > 0) {
        /* Decode up to temptative start point */
        if (_textiowrapper_decoder_setstate(self, &cookie) < 0)
            goto fail;
        DECODER_DECODE(input, skip_bytes, chars_decoded);
        if (chars_decoded <= chars_to_skip) {
            DECODER_GETSTATE();
            if (dec_buffer_len == 0) {
                /* Before pos and no bytes buffered in decoder => OK */
                cookie.dec_flags = dec_flags;
                chars_to_skip -= chars_decoded;
                break;
            }
            /* Skip back by buffered amount and reset heuristic */
            skip_bytes -= dec_buffer_len;
            skip_back = 1;
        }
        else {
            /* We're too far ahead, skip back a bit */
            skip_bytes -= skip_back;
            skip_back *= 2;
        }
    }
    if (skip_bytes <= 0) {
        skip_bytes = 0;
        if (_textiowrapper_decoder_setstate(self, &cookie) < 0)
            goto fail;
    }

    /* Note our initial start point. */
    cookie.start_pos += skip_bytes;
    cookie.chars_to_skip = Py_SAFE_DOWNCAST(chars_to_skip, Py_ssize_t, int);
    if (chars_to_skip == 0)
        goto finally;

    /* We should be close to the desired position.  Now feed the decoder one
     * byte at a time until we reach the `chars_to_skip` target.
     * As we go, note the nearest "safe start point" before the current
     * location (a point where the decoder has nothing buffered, so seek()
     * can safely start from there and advance to this location).
     */
    chars_decoded = 0;
    input = PyBytes_AS_STRING(next_input);
    input_end = input + PyBytes_GET_SIZE(next_input);
    input += skip_bytes;
    while (input < input_end) {
        Py_ssize_t n;

        DECODER_DECODE(input, (Py_ssize_t)1, n);
        /* We got n chars for 1 byte */
        chars_decoded += n;
        cookie.bytes_to_feed += 1;
        DECODER_GETSTATE();

        if (dec_buffer_len == 0 && chars_decoded <= chars_to_skip) {
            /* Decoder buffer is empty, so this is a safe start point. */
            cookie.start_pos += cookie.bytes_to_feed;
            chars_to_skip -= chars_decoded;
            cookie.dec_flags = dec_flags;
            cookie.bytes_to_feed = 0;
            chars_decoded = 0;
        }
        if (chars_decoded >= chars_to_skip)
            break;
        input++;
    }
    if (input == input_end) {
        /* We didn't get enough decoded data; signal EOF to get more. */
        PyObject *decoded = _PyObject_CallMethod(
            self->decoder, &_Py_ID(decode), "yO", "", /* final = */ Py_True);
        if (check_decoded(decoded) < 0)
            goto fail;
        chars_decoded += PyUnicode_GET_LENGTH(decoded);
        Py_DECREF(decoded);
        cookie.need_eof = 1;

        if (chars_decoded < chars_to_skip) {
            PyErr_SetString(PyExc_OSError,
                            "can't reconstruct logical file position");
            goto fail;
        }
    }

finally:
    res = PyObject_CallMethodOneArg(
            self->decoder, &_Py_ID(setstate), saved_state);
    Py_DECREF(saved_state);
    if (res == NULL)
        return NULL;
    Py_DECREF(res);

    /* The returned cookie corresponds to the last safe start point. */
    cookie.chars_to_skip = Py_SAFE_DOWNCAST(chars_to_skip, Py_ssize_t, int);
    return textiowrapper_build_cookie(&cookie);

fail:
    if (saved_state) {
        PyObject *exc = PyErr_GetRaisedException();
        res = PyObject_CallMethodOneArg(
                self->decoder, &_Py_ID(setstate), saved_state);
        _PyErr_ChainExceptions1(exc);
        Py_DECREF(saved_state);
        Py_XDECREF(res);
    }
    return NULL;
}

/*[clinic input]
@critical_section
_io.TextIOWrapper.truncate
    pos: object = None
    /
[clinic start generated code]*/

static PyObject *
_io_TextIOWrapper_truncate_impl(textio *self, PyObject *pos)
/*[clinic end generated code: output=90ec2afb9bb7745f input=8bddb320834c93ee]*/
{
    CHECK_ATTACHED(self)

    if (_PyFile_Flush((PyObject *)self) < 0) {
        return NULL;
    }

    return PyObject_CallMethodOneArg(self->buffer, &_Py_ID(truncate), pos);
}

static PyObject *
textiowrapper_repr(PyObject *op)
{
    PyObject *nameobj, *modeobj, *res, *s;
    int status;
    textio *self = textio_CAST(op);
    const char *type_name = Py_TYPE(self)->tp_name;

    CHECK_INITIALIZED(self);

    res = PyUnicode_FromFormat("<%.100s", type_name);
    if (res == NULL)
        return NULL;

    status = Py_ReprEnter(op);
    if (status != 0) {
        if (status > 0) {
            PyErr_Format(PyExc_RuntimeError,
                         "reentrant call inside %.100s.__repr__",
                         type_name);
        }
        goto error;
    }
    if (PyObject_GetOptionalAttr(op, &_Py_ID(name), &nameobj) < 0) {
        if (!PyErr_ExceptionMatches(PyExc_ValueError)) {
            goto error;
        }
        /* Ignore ValueError raised if the underlying stream was detached */
        PyErr_Clear();
    }
    if (nameobj != NULL) {
        s = PyUnicode_FromFormat(" name=%R", nameobj);
        Py_DECREF(nameobj);
        if (s == NULL)
            goto error;
        PyUnicode_AppendAndDel(&res, s);
        if (res == NULL)
            goto error;
    }
    if (PyObject_GetOptionalAttr(op, &_Py_ID(mode), &modeobj) < 0) {
        goto error;
    }
    if (modeobj != NULL) {
        s = PyUnicode_FromFormat(" mode=%R", modeobj);
        Py_DECREF(modeobj);
        if (s == NULL)
            goto error;
        PyUnicode_AppendAndDel(&res, s);
        if (res == NULL)
            goto error;
    }
    s = PyUnicode_FromFormat("%U encoding=%R>",
                             res, self->encoding);
    Py_DECREF(res);
    if (status == 0) {
        Py_ReprLeave(op);
    }
    return s;

  error:
    Py_XDECREF(res);
    if (status == 0) {
        Py_ReprLeave(op);
    }
    return NULL;
}


/* Inquiries */

/*[clinic input]
@critical_section
_io.TextIOWrapper.fileno
[clinic start generated code]*/

static PyObject *
_io_TextIOWrapper_fileno_impl(textio *self)
/*[clinic end generated code: output=21490a4c3da13e6c input=515e1196aceb97ab]*/
{
    CHECK_ATTACHED(self);
    return PyObject_CallMethodNoArgs(self->buffer, &_Py_ID(fileno));
}

/*[clinic input]
@critical_section
_io.TextIOWrapper.seekable
[clinic start generated code]*/

static PyObject *
_io_TextIOWrapper_seekable_impl(textio *self)
/*[clinic end generated code: output=ab223dbbcffc0f00 input=71c4c092736c549b]*/
{
    CHECK_ATTACHED(self);
    return PyObject_CallMethodNoArgs(self->buffer, &_Py_ID(seekable));
}

/*[clinic input]
@critical_section
_io.TextIOWrapper.readable
[clinic start generated code]*/

static PyObject *
_io_TextIOWrapper_readable_impl(textio *self)
/*[clinic end generated code: output=72ff7ba289a8a91b input=80438d1f01b0a89b]*/
{
    CHECK_ATTACHED(self);
    return PyObject_CallMethodNoArgs(self->buffer, &_Py_ID(readable));
}

/*[clinic input]
@critical_section
_io.TextIOWrapper.writable
[clinic start generated code]*/

static PyObject *
_io_TextIOWrapper_writable_impl(textio *self)
/*[clinic end generated code: output=a728c71790d03200 input=9d6c22befb0c340a]*/
{
    CHECK_ATTACHED(self);
    return PyObject_CallMethodNoArgs(self->buffer, &_Py_ID(writable));
}

/*[clinic input]
@critical_section
_io.TextIOWrapper.isatty
[clinic start generated code]*/

static PyObject *
_io_TextIOWrapper_isatty_impl(textio *self)
/*[clinic end generated code: output=12be1a35bace882e input=7f83ff04d4d1733d]*/
{
    CHECK_ATTACHED(self);
    return PyObject_CallMethodNoArgs(self->buffer, &_Py_ID(isatty));
}

/*[clinic input]
@critical_section
_io.TextIOWrapper.flush
[clinic start generated code]*/

static PyObject *
_io_TextIOWrapper_flush_impl(textio *self)
/*[clinic end generated code: output=59de9165f9c2e4d2 input=3ac3bf521bfed59d]*/
{
    CHECK_ATTACHED(self);
    CHECK_CLOSED(self);
    self->telling = self->seekable;
    if (_textiowrapper_writeflush(self) < 0)
        return NULL;
    return PyObject_CallMethodNoArgs(self->buffer, &_Py_ID(flush));
}

/*[clinic input]
@critical_section
_io.TextIOWrapper.close
[clinic start generated code]*/

static PyObject *
_io_TextIOWrapper_close_impl(textio *self)
/*[clinic end generated code: output=056ccf8b4876e4f4 input=8e12d7079d5ac5c1]*/
{
    PyObject *res;
    int r;
    CHECK_ATTACHED(self);

    res = _io_TextIOWrapper_closed_get_impl(self);
    if (res == NULL)
        return NULL;
    r = PyObject_IsTrue(res);
    Py_DECREF(res);
    if (r < 0)
        return NULL;

    if (r > 0) {
        Py_RETURN_NONE; /* stream already closed */
    }
    else {
        PyObject *exc = NULL;
        if (self->finalizing) {
            res = PyObject_CallMethodOneArg(self->buffer, &_Py_ID(_dealloc_warn),
                                            (PyObject *)self);
            if (res) {
                Py_DECREF(res);
            }
            else {
                PyErr_Clear();
            }
        }
        if (_PyFile_Flush((PyObject *)self) < 0) {
            exc = PyErr_GetRaisedException();
        }

        res = PyObject_CallMethodNoArgs(self->buffer, &_Py_ID(close));
        if (exc != NULL) {
            _PyErr_ChainExceptions1(exc);
            Py_CLEAR(res);
        }
        return res;
    }
}

static PyObject *
textiowrapper_iternext_lock_held(PyObject *op)
{
    _Py_CRITICAL_SECTION_ASSERT_OBJECT_LOCKED(op);
    PyObject *line;
    textio *self = textio_CAST(op);

    CHECK_ATTACHED(self);

    self->telling = 0;
    if (Py_IS_TYPE(self, self->state->PyTextIOWrapper_Type)) {
        /* Skip method call overhead for speed */
        line = _textiowrapper_readline(self, -1);
    }
    else {
        line = PyObject_CallMethodNoArgs(op, &_Py_ID(readline));
        if (line && !PyUnicode_Check(line)) {
            PyErr_Format(PyExc_OSError,
                         "readline() should have returned a str object, "
                         "not '%.200s'", Py_TYPE(line)->tp_name);
            Py_DECREF(line);
            return NULL;
        }
    }

    if (line == NULL)
        return NULL;

    if (PyUnicode_GET_LENGTH(line) == 0) {
        /* Reached EOF or would have blocked */
        Py_DECREF(line);
        Py_CLEAR(self->snapshot);
        self->telling = self->seekable;
        return NULL;
    }

    return line;
}

static PyObject *
textiowrapper_iternext(PyObject *op)
{
    PyObject *result;
    Py_BEGIN_CRITICAL_SECTION(op);
    result = textiowrapper_iternext_lock_held(op);
    Py_END_CRITICAL_SECTION();
    return result;
}

/*[clinic input]
@critical_section
@getter
_io.TextIOWrapper.name
[clinic start generated code]*/

static PyObject *
_io_TextIOWrapper_name_get_impl(textio *self)
/*[clinic end generated code: output=8c2f1d6d8756af40 input=26ecec9b39e30e07]*/
{
    CHECK_ATTACHED(self);
    return PyObject_GetAttr(self->buffer, &_Py_ID(name));
}

/*[clinic input]
@critical_section
@getter
_io.TextIOWrapper.closed
[clinic start generated code]*/

static PyObject *
_io_TextIOWrapper_closed_get_impl(textio *self)
/*[clinic end generated code: output=b49b68f443a85e3c input=7dfcf43f63c7003d]*/
{
    CHECK_ATTACHED(self);
    return PyObject_GetAttr(self->buffer, &_Py_ID(closed));
}

/*[clinic input]
@critical_section
@getter
_io.TextIOWrapper.newlines
[clinic start generated code]*/

static PyObject *
_io_TextIOWrapper_newlines_get_impl(textio *self)
/*[clinic end generated code: output=53aa03ac35573180 input=610df647e514b3e8]*/
{
    PyObject *res;
    CHECK_ATTACHED(self);
    if (self->decoder == NULL ||
        PyObject_GetOptionalAttr(self->decoder, &_Py_ID(newlines), &res) == 0)
    {
        Py_RETURN_NONE;
    }
    return res;
}

/*[clinic input]
@critical_section
@getter
_io.TextIOWrapper.errors
[clinic start generated code]*/

static PyObject *
_io_TextIOWrapper_errors_get_impl(textio *self)
/*[clinic end generated code: output=dca3a3ef21b09484 input=b45f983e6d43c4d8]*/
{
    CHECK_INITIALIZED(self);
    return Py_NewRef(self->errors);
}

/*[clinic input]
@critical_section
@getter
_io.TextIOWrapper._CHUNK_SIZE
[clinic start generated code]*/

static PyObject *
_io_TextIOWrapper__CHUNK_SIZE_get_impl(textio *self)
/*[clinic end generated code: output=039925cd2df375bc input=e9715b0e06ff0fa6]*/
{
    CHECK_ATTACHED(self);
    return PyLong_FromSsize_t(self->chunk_size);
}

/*[clinic input]
@critical_section
@setter
_io.TextIOWrapper._CHUNK_SIZE
[clinic start generated code]*/

static int
_io_TextIOWrapper__CHUNK_SIZE_set_impl(textio *self, PyObject *value)
/*[clinic end generated code: output=edb86d2db660a5ab input=32fc99861db02a0a]*/
{
    Py_ssize_t n;
    CHECK_ATTACHED_INT(self);
    if (value == NULL) {
        PyErr_SetString(PyExc_AttributeError, "cannot delete attribute");
        return -1;
    }
    n = PyNumber_AsSsize_t(value, PyExc_ValueError);
    if (n == -1 && PyErr_Occurred())
        return -1;
    if (n <= 0) {
        PyErr_SetString(PyExc_ValueError,
                        "a strictly positive integer is required");
        return -1;
    }
    self->chunk_size = n;
    return 0;
}

static PyMethodDef incrementalnewlinedecoder_methods[] = {
    _IO_INCREMENTALNEWLINEDECODER_DECODE_METHODDEF
    _IO_INCREMENTALNEWLINEDECODER_GETSTATE_METHODDEF
    _IO_INCREMENTALNEWLINEDECODER_SETSTATE_METHODDEF
    _IO_INCREMENTALNEWLINEDECODER_RESET_METHODDEF
    {NULL}
};

static PyGetSetDef incrementalnewlinedecoder_getset[] = {
    {"newlines", incrementalnewlinedecoder_newlines_get, NULL, NULL},
    {NULL}
};

static PyType_Slot nldecoder_slots[] = {
    {Py_tp_dealloc, incrementalnewlinedecoder_dealloc},
    {Py_tp_doc, (void *)_io_IncrementalNewlineDecoder___init____doc__},
    {Py_tp_methods, incrementalnewlinedecoder_methods},
    {Py_tp_getset, incrementalnewlinedecoder_getset},
    {Py_tp_traverse, incrementalnewlinedecoder_traverse},
    {Py_tp_clear, incrementalnewlinedecoder_clear},
    {Py_tp_init, _io_IncrementalNewlineDecoder___init__},
    {0, NULL},
};

PyType_Spec nldecoder_spec = {
    .name = "_io.IncrementalNewlineDecoder",
    .basicsize = sizeof(nldecoder_object),
    .flags = (Py_TPFLAGS_DEFAULT | Py_TPFLAGS_BASETYPE | Py_TPFLAGS_HAVE_GC |
              Py_TPFLAGS_IMMUTABLETYPE),
    .slots = nldecoder_slots,
};


static PyMethodDef textiowrapper_methods[] = {
    _IO_TEXTIOWRAPPER_DETACH_METHODDEF
    _IO_TEXTIOWRAPPER_RECONFIGURE_METHODDEF
    _IO_TEXTIOWRAPPER_WRITE_METHODDEF
    _IO_TEXTIOWRAPPER_READ_METHODDEF
    _IO_TEXTIOWRAPPER_READLINE_METHODDEF
    _IO_TEXTIOWRAPPER_FLUSH_METHODDEF
    _IO_TEXTIOWRAPPER_CLOSE_METHODDEF

    _IO_TEXTIOWRAPPER_FILENO_METHODDEF
    _IO_TEXTIOWRAPPER_SEEKABLE_METHODDEF
    _IO_TEXTIOWRAPPER_READABLE_METHODDEF
    _IO_TEXTIOWRAPPER_WRITABLE_METHODDEF
    _IO_TEXTIOWRAPPER_ISATTY_METHODDEF

    _IO_TEXTIOWRAPPER_SEEK_METHODDEF
    _IO_TEXTIOWRAPPER_TELL_METHODDEF
    _IO_TEXTIOWRAPPER_TRUNCATE_METHODDEF

    {"__getstate__", _PyIOBase_cannot_pickle, METH_NOARGS},
    {NULL, NULL}
};

static PyMemberDef textiowrapper_members[] = {
    {"encoding", _Py_T_OBJECT, offsetof(textio, encoding), Py_READONLY},
    {"buffer", _Py_T_OBJECT, offsetof(textio, buffer), Py_READONLY},
    {"line_buffering", Py_T_BOOL, offsetof(textio, line_buffering), Py_READONLY},
    {"write_through", Py_T_BOOL, offsetof(textio, write_through), Py_READONLY},
    {"_finalizing", Py_T_BOOL, offsetof(textio, finalizing), 0},
    {"__weaklistoffset__", Py_T_PYSSIZET, offsetof(textio, weakreflist), Py_READONLY},
    {"__dictoffset__", Py_T_PYSSIZET, offsetof(textio, dict), Py_READONLY},
    {NULL}
};

static PyGetSetDef textiowrapper_getset[] = {
    _IO_TEXTIOWRAPPER_NAME_GETSETDEF
    _IO_TEXTIOWRAPPER_CLOSED_GETSETDEF
    _IO_TEXTIOWRAPPER_NEWLINES_GETSETDEF
    _IO_TEXTIOWRAPPER_ERRORS_GETSETDEF
    _IO_TEXTIOWRAPPER__CHUNK_SIZE_GETSETDEF
    {NULL}
};

PyType_Slot textiowrapper_slots[] = {
    {Py_tp_dealloc, textiowrapper_dealloc},
    {Py_tp_repr, textiowrapper_repr},
    {Py_tp_doc, (void *)_io_TextIOWrapper___init____doc__},
    {Py_tp_traverse, textiowrapper_traverse},
    {Py_tp_clear, textiowrapper_clear},
    {Py_tp_iternext, textiowrapper_iternext},
    {Py_tp_methods, textiowrapper_methods},
    {Py_tp_members, textiowrapper_members},
    {Py_tp_getset, textiowrapper_getset},
    {Py_tp_init, _io_TextIOWrapper___init__},
    {0, NULL},
};

PyType_Spec textiowrapper_spec = {
    .name = "_io.TextIOWrapper",
    .basicsize = sizeof(textio),
    .flags = (Py_TPFLAGS_DEFAULT | Py_TPFLAGS_BASETYPE | Py_TPFLAGS_HAVE_GC |
              Py_TPFLAGS_IMMUTABLETYPE),
    .slots = textiowrapper_slots,
};
