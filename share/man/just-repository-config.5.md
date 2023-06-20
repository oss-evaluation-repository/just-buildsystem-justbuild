% JUST REPOSITORY CONFIG(5) | File Formats Manual

NAME
====

just repository config -- The format of the repository config used by
**just(1)**

DESCRIPTION
===========

`just`'s repository configuration is read as JSON. Any other
serialization describing the same JSON object is equivalent. We assume,
that in JSON objects, each key occurs at most once; it is implementation
defined how repetitions of the same key are treated.

File root description
---------------------

Each repository can have multiple *`file roots`*. Each file root is
defined as a non-empty JSON list with its first element being a string,
which determines the type and semantic of the subsequent elements:

 - *`"file"`* refers to a file root that is located in the file system.
   The list has to be of length 2 and the second argument contains the
   path to the file root.

 - *`"git tree"`* refers to a file root that is available as part of a
   Git repository. The list has to be of length 3 with the remaining two
   elements being:

   1. The *`git tree hash`*, which is sufficient to describe the content
      of an entire tree including its sub-trees and blobs. The tree hash
      has to be specified in hex encoding.
   2. The path to a Git repository on the file system with the promise
      that it contains the aforementioned *`git tree hash`*.

Repository description
----------------------

A single *`repository description`* is defined as a JSON object, which
contains *`file roots`*, file names, and bindings to other repositories.
Specifically the following fields are supported:

 - *`"workspace_root"`* contains the *`file root`* where source files
   are located. If this entry is missing for the main repository, `just`
   will perform the normal workspace root resolution starting from the
   current working directory.

 - *`"target_root"`* contains the *`file root`* where the target files
   are located. If this entry is missing, the workspace root is taken.

 - *`"target_file_name"`* contains the file name of target files to use.
   If this entry is missing, the default target file name *`TARGETS`* is
   used.

 - *`"rule_root"`* contains the *`file root`* where the rule files are
   located. If this entry is missing, the target root is taken.

 - *`"rule_file_name"`* contains the file name of rule files to use. If
   this entry is missing, the default rule file name *`RULES`* is used.

 - *`"expression_root"`* contains the *`file root`* where the expression
   files are located. If this entry is missing, the rule root is taken.

 - *`"expression_file_name"`* contains the file name of expression files
   to use. If this entry is missing, the default expression file name
   *`EXPRESSIONS`* is used.

 - *`"bindings"`* contains a JSON object that defines bindings to other
   repositories by mapping local repository names to global ones. The
   object's key is local name, while the value is a string representing
   the global name.

Note that any other unsupported field is accepted but ignored. There are
no guarantees that any yet unsupported field may not become meaningful
in future versions.

Repository configuration format
-------------------------------

The repository configuration format is a JSON object with the following
keys:

 - *`"main"`* contains a string, which defines the repository name to
   consider by default if not explicitly specified on the command line
   (i.e., via **`--main`**). This entry is optional and if omitted the
   empty string is used.

 - *`"repositories"`* contains a JSON object that defines all
   repositories by mapping global repository names to *repository
   descriptions* documented above. This entry is optional and if
   omitted an empty JSON object is used.

NOTES
=====

Although the repository configuration is human-readable and can be
written by hand, in many cases it will be generated by an independent
tool. **just-mr(1)** is one such tool that can be used for configuration
generation, but not necessarily the only one.

See also
========

**just(1)**, **just-mr(1)**, **just-mr-repository-config(5)**