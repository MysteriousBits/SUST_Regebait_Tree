# SUST_Ragebait_Tree | Team Code Library & Codebook

Git repository for the **SUST_Ragebait_Tree** team. This repo contains our dsa code library, templates, scripts and the LaTeX-based codebook.

---

## 📖 Modifying the Codebook

The codebook uses LaTeX to build the PDF from source code files and theoretical texts. It is optimized for a 3-column layout.

### Adding new chapter:
1.  **Create the file**: Add a `<chapter_name>.tex` file in `codebook/chapters/`.
2.  **Register the chapter**: Add `\input{chapters/chapter_name}` in the main `codebook/codebook.tex` file.

---

## 💻 Adding Code

All code must be formatted to ensure it fits correctly with minimum required space.

### To add code:
1.  **Create the source**: Make a file (e.g., `<code.cpp>`) in the appropriate directory inside `code_library/`.
2.  **Paste and Format**: 
    * Paste your code into the file.
    * Ensure you have a code formatter installed (the **C/C++ extension** in VS Code includes this).
    * **Reformat the document.** The configuration from the root `.clang-format` will be applied automatically to minimize space.
3.  **Link to LaTeX**: In the related `<chapter_name>.tex` file inside `codebook/chapters/`, add the following:
    ```latex
    \code{topic_name}{path_to_code}
    ```
    *Note: `path_to_code` is relative to the `code_library/` directory.*

---

## 🛠 Prerequisites

To build the codebook locally, ensure you have:
* **LaTeX Distribution**: TeX Live, MiKTeX, or MacTeX.
* **Clang-Format**: For consistent code styling.
* **Git**: For version control.

---

## 🛠 Build Locally

You can compile the codebook using the command line or a dedicated LaTeX editor.

### Command Line
Run the following command from the root directory to handle all passes (Table of Contents, SyncTeX, and Bibliography) automatically:
```bash
cd codebook
latexmk -pdf -synctex=1 -interaction=nonstopmode codebook.tex
```

### Reset the cache 
Sometimes, build failure will generate cache and the cache needs to be resetted in order to do a correct compilation.
Run the following command in order to reset cache (sometimes)

```
latexmk -C 
```