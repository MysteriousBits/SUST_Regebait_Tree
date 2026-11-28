import os
import re

# Auto-detect base directory for code_library
if os.path.exists("code_library"):
    BASE_DIR = "."
elif os.path.exists("../code_library"):
    BASE_DIR = ".."
else:
    BASE_DIR = "."

OUTPUT_TEX = "generated_contents.tex"
VALID_EXTENSIONS = {
    ".cpp", ".h", ".hpp", ".json", ".txt", ".tex", 
    ".sublime-snippet", ".sublime-build", ".sh", ".bash"
}

# COMPLETE Table of Contents structure with wide-reaching candidate naming
EXACT_TOC = [
    {
        "chapter": "Templates and Scripts",
        "folder_candidates": ["scripts", "template", "templates"],
        "sections": [
            ("sublime", ["cp.sublime-build", "sublime", "sublime.cpp", "sublime.txt", "sublime.json", "sublime-snippet", "cpp.sublime-build"]),
            ("vs code", ["tasks.json", "vscode", "vs_code", "settings.json", "cpp.json", "vscode.json"]),
            ("Interactor", ["interactor.sh", "interactor.cpp", "interactor", "interactive.cpp", "tester.cpp"]),
            ("debug.h", ["debug.h", "debug.cpp", "debug", "dbg.h"]),
        ]
    },
    {
        "chapter": "Number Theory",
        "folder_candidates": ["nt", "number_theory"],
        "sections": [
            ("mini mod", ["mini_mod.cpp", "minimod.cpp", "mod.cpp"]),
            ("Binomial Coeffecient", ["binomial_coeffecient.cpp", "binomial_coefficient.cpp", "ncr.cpp", "binomial.cpp"]),
            ("Sieve, SPF, Phi", ["sieve.cpp", "sieve_spf_phi.cpp", "sieve_spf.cpp", "spf.cpp"]),
            ("Segmented Sieve", ["segmented_sieve.cpp", "seg_sieve.cpp"]),
            ("Safe LCM", ["safe_lcm.cpp", "lcm.cpp"]),
            ("Extended GCD", ["ext_gcd.cpp", "extended_gcd.cpp", "egcd.cpp", "extgcd.cpp"]),
            ("CRT", ["crt.cpp", "chinese_remainder_theorem.cpp", "crt.h"]),
            ("Diophantine Equation", ["diophantine.cpp", "diophantine_equation.cpp"]),
            ("Pollar Rho Factorization", ["pollard_rho.cpp", "pollar_rho.cpp", "pollard.cpp"]),
        ]
    },
    {
        "chapter": "Dynamic Programming",
        "folder_candidates": ["dp", "dynamic_programming"],
        "sections": [
            ("SOS DP", ["sos_dp.cpp", "sos.cpp", "sosdp.cpp"]),
            ("CHT", ["cht.cpp", "convex_hull_trick.cpp"]),
            ("CHT Dynamic", ["cht_dynamic.cpp", "dynamic_cht.cpp", "dyn_cht.cpp"]),
        ]
    },
    {
        "chapter": "Data Structure",
        "folder_candidates": ["ds", "data_structures", "data_structure"],
        "sections": [
            ("Fenwick Tree", ["fenwick.cpp", "fenwick_tree.cpp", "bit.cpp"]),
            ("Fenwick 2D (Compressed)", ["fenwick2d.cpp", "fenwick_2d.cpp", "fenwick_2d_compressed.cpp"]),
            ("BIT 2D", ["pref_sum_2D.cpp", "bit2d.cpp", "bit_2d.cpp"]),
            ("Segment Tree", ["segtree.cpp", "segment_tree.cpp"]),
            ("Lazy Propagation", ["lazy_propagation.cpp", "segtree_lazy.cpp", "lazy.cpp"]),
            ("Persistent Segment Tree", ["persistent_segtree.cpp", "pst.cpp", "persistent_seg.cpp"]),
            ("Merge Sort Tree", ["mst.cpp", "merge_sort_tree.cpp"]),
            ("Merse Sort Tree with Update", ["mst_with_update.cpp", "merse_sort_tree_with_update.cpp", "mst_update.cpp"]),
            ("Treap", ["treap.cpp"]),
            ("Segment Tree 2D (1 based)", ["segtree_2D.cpp", "segtree_2d.cpp"]),
            ("Segment Tree 2D (Index compression)", ["segtree_2D_index_comp.cpp", "segtree_2d_index_compression.cpp"]),
            ("DSU", ["dsu.cpp", "disjoint_set.cpp"]),
            ("SQRT Decomposition", ["sqrt_decomposition.cpp", "sqrt.cpp", "sqrt_decomp.cpp"]),
            ("MOs Algorithm", ["normal_mo.cpp", "mos_algorithm.cpp", "mo.cpp"]),
            ("MOs with updates", ["mos_with_updates.cpp", "mo_update.cpp"]),
            ("Implicit Treap", ["implicit_treap.cpp", "treap_implicit.cpp", "implicit.cpp", "treap.cpp"]),
            ("Wavelet Tree", ["wavelet_tree.cpp", "wavelet.cpp"]),
            ("Sparse Table (RMQ)", ["sparse_table.cpp", "rmq.cpp"]),
            ("Prefix Sum 2D", ["pref_sum_2D.cpp", "prefix_sum_2d.cpp"]),
            ("Prefix Sum 3D", ["pref_sum_3D.cpp", "prefix_sum_3d.cpp"]),
        ]
    },
    {
        "chapter": "Graph",
        "folder_candidates": ["graph"],
        "sections": [
            ("Dijkstra", ["dijkstra.cpp"]),
            ("Bellmanford", ["bellmanford.cpp", "bellman_ford.cpp"]),
            ("BCC, Bridge, AP", ["bcc_bridge_ap.cpp", "bcc.cpp", "bridge_ap.cpp"]),
            ("2CC", ["2cc.cpp", "twocc.cpp"]),
            ("LCA", ["lca.cpp", "binary_lifting.cpp"]),
            ("SCC", ["scc.cpp", "tarjan.cpp", "kosaraju.cpp", "strongly_connected_components.cpp"]),
            ("Kosaraju", ["kosaraju.cpp"]),
            ("HLD", ["hld.cpp", "heavy_light_decomposition.cpp"]),
            ("Centroid Decomposition", ["centroid_decomposition.cpp", "centroid.cpp", "cd.cpp", "centroid_decomp.cpp"]),
            ("Arpa's Trick", ["arpas_trick.cpp", "arpa_trick.cpp"]),
        ]
    },
    {
        "chapter": "Flow and Matching",
        "folder_candidates": ["flow_matching", "flow_and_matching", "flow"],
        "sections": [
            ("Min Cost Max Flow", ["min_cost_max_flow.cpp", "mcmf.cpp", "mincost_maxflow.cpp"]),
            ("Dinic", ["dinic.cpp", "dinics.cpp"]),
            ("Edmonds Karp", ["edmonds_karp.cpp", "edmond_karp.cpp", "ek.cpp", "edmonds.cpp", "edmondkarp.cpp"]),
            ("HopcroftKarp", ["hopcroft_karp.cpp", "hopcroftkarp.cpp", "hopcroft.cpp"]),
        ]
    },
    {
        "chapter": "String",
        "folder_candidates": ["string", "strings"],
        "sections": [
            ("Trie", ["trie.cpp"]),
            ("Bit Trie", ["bit_trie.cpp", "bittrie.cpp"]),
            ("Z Algorithm", ["z_algorithm.cpp", "z.cpp", "z_function.cpp", "zalgo.cpp", "z-algorithm.cpp"]),
            ("KMP", ["kmp.cpp", "KMP.h"]),
            ("Suffix Array", ["suffix_array.cpp", "sa.cpp", "SuffixArray.h"]),
            ("Suffix Automaton", ["suffix_automation.cpp", "suffix_automaton.cpp", "sam.cpp"]),
            ("Manacher", ["manacher.cpp", "Manacher.h"]),
            ("Aho Corasick", ["aho_corasick.cpp", "aho.cpp", "AhoCorasick.h"]),
            ("Min Lexic Rotation", ["min_lexic_rotation.cpp", "minimal_rotation.cpp", "min_rotation.cpp", "minlex.cpp"]),
            ("Longest Palindrome", ["longest_palindrome.cpp", "palindrome.cpp"]),
            ("Wildcard Matching", ["wildcard_matching.cpp", "wildcard.cpp", "wildcard_match.cpp"]),
            ("Hashing", ["hashing.cpp", "string_hash.cpp", "hash.cpp"]),
            ("2D Hash", ["2d_hash.cpp", "hash_2d.cpp", "2dhash.cpp", "hash2d.cpp", "two_d_hash.cpp", "twodhash.cpp", "matrix_hash.cpp", "grid_hash.cpp", "string_hash_2d.cpp"]),
        ]
    },
    {
        "chapter": "Numerical",
        "folder_candidates": ["numerical", "math"],
        "sections": [
            ("FFT", ["fft.cpp", "fft.h", "fast_fourier_transform.cpp"]),
            ("FFT With mod M", ["fft_mod.cpp", "fft_with_mod_m.cpp", "fft_mod_m.cpp", "fftmod.cpp"]),
            ("NTT", ["ntt.cpp", "ntt.h"]),
            ("FWHT", ["fwht.cpp", "fwt.cpp", "walsh_hadamard.cpp"]),
        ]
    },
    {
        "chapter": "Linear Algebra",
        "folder_candidates": ["matrix", "linear_algebra"],
        "sections": [
            ("The Matrix Class", ["matrix_class.cpp", "matrix.cpp"]),
            ("Gaussian Elimination", ["gaussian_elimination.cpp", "gauss.cpp"]),
            ("Determinant", ["determinant.cpp", "det.cpp"]),
            ("Matrix Inverse", ["matrix_inverse.cpp", "inverse.cpp"]),
            ("Xor Basis", ["xor_basis.cpp", "linear_basis.cpp"]),
        ]
    },
    {
        "chapter": "Geometry",
        "folder_candidates": ["geometry_shohag_bhai", "geometry"],
        "sections": [
            ("Full Template", ["shohag_bhai.cpp", "full_template.cpp", "geometry.cpp", "shohag.cpp", "kactl.cpp", "geo.cpp"]),
        ]
    },
    {
        "chapter": "Miscellaneous",
        "folder_candidates": ["misc", "miscellaneous"],
        "sections": [
            ("Interval Container", ["interval_container.cpp", "intervals.cpp", "interval.cpp", "odt.cpp", "chtholly.cpp"]),
            ("Efficient Mask Traversal", ["efficient_mask_traversal.cpp", "mask_traversal.cpp"]),
            ("Generationg Permutations", ["generating_permutations.cpp", "generationg_permutations.cpp", "permutations.cpp"]),
            ("Iterating over Submasks", ["iterating_submasks.cpp", "submask.cpp"]),
            ("Random", ["random.cpp", "rng.cpp", "rand.cpp"]),
            ("Index compression", ["index_compression.cpp", "coordinate_compression.cpp"]),
            ("pbds", ["pbds.cpp"]),
            ("Bitset", ["bitset.cpp"]),
            ("Primes", ["primes.cpp"]),
            ("Digit Range Sum", ["digit_range_sum.cpp", "digit_dp.cpp", "digit_sum.cpp"]),
            ("Custom Hash", ["custom_hash.cpp", "gp_hash_table.cpp"]),
        ]
    }
]

def clean_name(s):
    return re.sub(r'[^a-z0-9]', '', s.lower())

def load_existing_descriptions():
    descriptions = {}
    pattern = r'\\codeWithDescription\*?\{([^}]+)\}\s*\{([^}]+)\}\s*\[(.*?)\]'
    for root, _, files in os.walk(BASE_DIR):
        if ".git" in root or "build" in root: continue
        for f in files:
            if f.endswith(".tex") and f != OUTPUT_TEX and f != "main.tex":
                try:
                    with open(os.path.join(root, f), "r", encoding="utf-8") as fo:
                        for title, file_key, desc in re.findall(pattern, fo.read(), re.DOTALL):
                            descriptions[title.strip().lower()] = desc.strip()
                            descriptions[os.path.basename(file_key).strip().lower()] = desc.strip()
                except: pass
    return descriptions

def find_file(folder_candidates, candidate_filenames):
    clean_cands = [clean_name(os.path.splitext(c)[0]) for c in candidate_filenames]
    
    # Strategy 1: Targeted folder scan
    for f_cand in folder_candidates:
        folder_path = os.path.join(BASE_DIR, "code_library", f_cand)
        if os.path.exists(folder_path):
            for root, _, files in os.walk(folder_path):
                for f in files:
                    if os.path.splitext(f)[1].lower() in VALID_EXTENSIONS:
                        f_clean = clean_name(os.path.splitext(f)[0])
                        if f_clean in clean_cands:
                            return os.path.join(root, f).replace("\\", "/"), root

    # Strategy 2: Ultra-fuzzy global workspace fallback match
    for root, _, files in os.walk(BASE_DIR):
        if any(p in root for p in [".git", "build", ".vscode"]): continue
        for f in files:
            if os.path.splitext(f)[1].lower() in VALID_EXTENSIONS:
                f_clean = clean_name(os.path.splitext(f)[0])
                for c_clean in clean_cands:
                    if f_clean == c_clean or (len(f_clean) > 2 and f_clean in c_clean) or (len(c_clean) > 2 and c_clean in f_clean):
                        return os.path.join(root, f).replace("\\", "/"), root
                            
    return None, None

def find_formulae_file():
    for root, _, files in os.walk(BASE_DIR):
        if ".git" in root or "build" in root: continue
        for f in files:
            if f.endswith(".tex") and ("formula" in f.lower() or "math" in f.lower()):
                return os.path.join(root, f).replace("\\", "/")
    return None

def build_tex():
    lines = []
    missing_sections = []

    print("Parsing workspace for template descriptions...")
    descriptions = load_existing_descriptions()

    for item in EXACT_TOC:
        chapter_title = item["chapter"]
        lines.append(f"\\chapter{{{chapter_title}}}")

        for exact_section_title, candidates in item["sections"]:
            matched_file, _ = find_file(item["folder_candidates"], candidates)
            lines.append(f"\\section{{{exact_section_title}}}")
            
            if not matched_file:
                missing_sections.append((chapter_title, exact_section_title, candidates))
                lines.append(f"\\noindent\\color{{red}}\\textbf{{[Missing Code File: Looked for {candidates[0]}]}}\\color{{black}}")
                lines.append("")
                continue

            norm_title = exact_section_title.strip().lower()
            file_key = os.path.basename(matched_file).strip().lower()
            has_description = (norm_title in descriptions or file_key in descriptions)

            if has_description:
                desc_text = descriptions.get(norm_title) or descriptions.get(file_key)
                lines.append(f"\\codeWithDescription{{{exact_section_title}}}{{{matched_file}}}[\n{desc_text}\n]")
            else:
                ext = os.path.splitext(matched_file)[1].lower()
                if ext == ".tex": lines.append(f"\\input{{{matched_file}}}")
                elif ext in {".json", ".txt", ".sublime-snippet", ".sublime-build", ".sh"}:
                    lines.append(f"\\lstinputlisting[language=bash]{{{matched_file}}}")
                else: lines.append(f"\\lstinputlisting[language=C++]{{{matched_file}}}")
            lines.append("")

    # Formulae internal chapter check
    formulae_file = find_formulae_file()
    if formulae_file:
        has_internal_chapter = False
        try:
            with open(formulae_file, "r", encoding="utf-8") as f:
                if "\\chapter" in f.read(): has_internal_chapter = True
        except: pass
        
        if not has_internal_chapter: lines.append("\\chapter{Formulae}")
        lines.append(f"\\input{{{formulae_file}}}")
    else:
        lines.append("\\chapter{Formulae}\n% Formulae file not found.")

    with open(OUTPUT_TEX, "w", encoding="utf-8") as f:
        f.write("\n".join(lines))

    print("\n" + "="*50 + "\n             CRITICAL FILE AUDIT REPORT             \n" + "="*50)
    if missing_sections:
        for ch, sec, cands in missing_sections:
            print(f"❌ MISSING: [{ch}] -> \"{sec}\" (Target: {cands[0]})")
        print("\n👉 Fuzzy scan complete. If items are still missing, verify they aren't completely untracked or deleted.")
    else:
        print("🙌 All files perfectly mapped and generated!")
    print("="*50 + "\n")

if __name__ == "__main__":
    build_tex()