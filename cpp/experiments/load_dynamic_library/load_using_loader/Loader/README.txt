i mean, if i write a loader for dll, if the loader is header only, i can simply include it

however if my loader contains source files, like .cpp, then user has to also link to it?

---

Yes, you're correct. If your loader for the DLL contains only header files and doesn't have any associated source files (e.g., .cpp files), then users can simply include the header files in their project, and the loader's functionality will be available.

However, if your loader contains source files (.cpp files), users will need to compile and link those source files along with their own code to use the loader. In this case, the loader becomes a separate compilation unit, and users would need to ensure that the loader's source files are compiled and linked along with their project.
