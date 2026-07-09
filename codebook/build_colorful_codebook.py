import os

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

# EXACT Table of Contents structure matched to repo file tree
EXACT_TOC = [
    {
        "chapter": "Templates and Scripts",
        "folder_candidates": ["scripts", "template", "templates"],
        "sections": [
            ("sublime", [
                "cp.sublime-build", "sublime", "sublime.cpp", "sublime.txt", 
                "sublime.json", "sublime-snippet", "cpp.sublime-build", 
                "sublime_settings", "sublime_template"
            ]),
            ("vs code", [
                "tasks.json", "vscode", "vs_code", "settings.json", "cpp.json", 
                "vscode.json", "vs_code.json", "vscode.cpp", "vs_code.cpp"
            ]),
            ("Interactor", [
                "interactor.sh", "interactor.cpp", "interactor", "interactive.cpp", 
                "tester.cpp", "interactor.h", "interactive.sh"
            ]),
            ("debug.h", [
                "debug.h", "debug.cpp", "debug", "dbg.h"
            ]),
        ]
    },
    {
        "chapter": "Number Theory",
        "folder_candidates": ["nt", "number_theory"],
        "sections": [
            ("mini mod", ["mini_mod.cpp", "minimod.cpp", "mod.cpp", "mini_mod"]),
            ("Binomial Coeffecient", ["binomial_coeffecient.cpp", "binomial_coefficient.cpp", "ncr.cpp", "binomial.cpp"]),
            ("Sieve, SPF, Phi", ["sieve.cpp", "sieve_spf_phi.cpp", "sieve_spf.cpp", "spf.cpp"]),
            ("Segmented Sieve", ["segmented_sieve.cpp", "seg_sieve.cpp"]),
            ("Safe LCM", ["safe_lcm.cpp", "lcm.cpp"]),
            ("Extended GCD", ["ext_gcd.cpp", "extended_gcd.cpp", "egcd.cpp"]),
            ("CRT", ["crt.cpp", "chinese_remainder_theorem.cpp"]),
            ("Diophantine Equation", ["diophantine.cpp", "diophantine_equation.cpp"]),
            ("Pollar Rho Factorization", ["pollard_rho.cpp", "pollar_rho.cpp", "pollard.cpp", "pollar_rho_factorization.cpp"]),
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
            ("Segment Tree 2D (1 based)", ["segtree_2D.cpp", "segtree_2d.cpp", "segtree_2d_1based.cpp"]),
            ("Segment Tree 2D (Index compression)", ["segtree_2D_index_comp.cpp", "segtree_2d_index_compression.cpp", "segtree_2d_comp.cpp"]),
            ("DSU", ["dsu.cpp", "disjoint_set.cpp"]),
            ("SQRT Decomposition", ["sqrt_decomposition.cpp", "sqrt.cpp", "sqrt_decomp.cpp"]),
            ("MOs Algorithm", ["normal_mo.cpp", "mos_algorithm.cpp", "mo.cpp", "mos.cpp"]),
            ("MOs with updates", ["mos_with_updates.cpp", "mo_update.cpp", "mo_updates.cpp"]),
            ("Treap", ["implicit_treap.cpp", "treap.cpp"]),
            ("Wavelet Tree", ["wavelet_tree.cpp", "wavelet.cpp"]),
            ("Sparse Table (RMQ)", ["sparse_table.cpp", "rmq.cpp", "sparse.cpp"]),
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
            ("BCC, Bridge, AP", ["bcc_bridge_ap.cpp", "bcc.cpp", "bridge_ap.cpp", "bridges.cpp"]),
            ("2CC", ["2cc.cpp", "twocc.cpp", "2_edge_connected.cpp"]),
            ("LCA", ["lca.cpp", "binary_lifting.cpp"]),
            ("SCC", ["scc.cpp", "tarjan.cpp"]),
            ("Kosaraju", ["kosaraju.cpp"]),
            ("HLD", ["hld.cpp", "heavy_light_decomposition.cpp"]),
            ("Centroid Decomposition", ["centroid_decomposition.cpp", "centroid.cpp", "cd.cpp", "centroid_decomp.cpp"]),
            ("Arpa's Trick", ["arpas_trick.cpp", "arpa.cpp", "arpa_trick.cpp"]),
        ]
    },
    {
        "chapter": "Flow and Matching",
        "folder_candidates": ["flow_matching", "flow_and_matching", "flow"],
        "sections": [
            ("Min Cost Max Flow", ["min_cost_max_flow.cpp", "mcmf.cpp", "mincost_maxflow.cpp"]),
            ("Dinic", ["dinic.cpp", "dinics.cpp"]),
            ("HopcroftKarp", ["hopcroft_karp.cpp", "hopcroftkarp.cpp", "hopcroft.cpp"]),
        ]
    },
    {
        "chapter": "String",
        "folder_candidates": ["string", "strings"],
        "sections": [
            ("Trie", ["trie.cpp"]),
            ("Bit Trie", ["bit_trie.cpp", "bittrie.cpp"]),
            ("Z Algorithm", ["z_algorithm.cpp", "z.cpp", "z_function.cpp", "zalgo.cpp"]),
            ("KMP", ["kmp.cpp", "KMP.h"]),
            ("Suffix Array", ["suffix_array.cpp", "sa.cpp", "SuffixArray.h"]),
            ("Suffix Automaton", [
                "suffix_automation.cpp", "suffix_automaton.cpp", 
                "suffix_automata.cpp", "sam.cpp", "automaton.cpp"
            ]),
            ("Manacher", ["manacher.cpp", "manachers.cpp", "Manacher.h"]),
            ("Aho Corasick", ["aho_corasick.cpp", "aho.cpp", "ahocorasick.cpp", "AhoCorasick.h"]),
            ("Min Lexic Rotation", ["min_lexic_rotation.cpp", "minimal_rotation.cpp", "min_rotation.cpp", "minlex.cpp"]),
            ("Longest Palindrome", ["longest_palindrome.cpp", "palindrome.cpp"]),
            ("Wildcard Matching", ["wildcard_matching.cpp", "wildcard.cpp"]),
            ("Hashing", ["hashing.cpp", "string_hash.cpp", "hash.cpp", "hashing.h"]),
            ("2D Hash", ["2d_hash.cpp", "hash_2d.cpp", "hash2d.cpp", "2dhash.cpp", "hashing2D.cpp"]),
        ]
    },
    {
        "chapter": "Numerical",
        "folder_candidates": ["numerical", "math"],
        "sections": [
            ("FFT", ["fft.cpp"]),
            ("FFT With mod M", ["fft_mod.cpp", "fft_with_mod_m.cpp", "fft_mod_m.cpp"]),
            ("NTT", ["ntt.cpp"]),
            ("FWHT", ["fwht.cpp", "fwt.cpp", "walsh_hadamard.cpp"]),
        ]
    },
    {
        "chapter": "Linear Algebra",
        "folder_candidates": ["matrix", "linear_algebra"],
        "sections": [
            ("The Matrix Class", ["matrix_class.cpp", "matrix.cpp"]),
            ("Gaussian Elimination", ["gaussian_elimination.cpp", "gauss.cpp", "gaussian.cpp"]),
            ("Determinant", ["determinant.cpp", "det.cpp"]),
            ("Matrix Inverse", ["matrix_inverse.cpp", "inverse.cpp"]),
            ("Xor Basis", ["xor_basis.cpp", "linear_basis.cpp", "basis.cpp"]),
        ]
    },
    {
        "chapter": "Geometry",
        "folder_candidates": ["geometry_shohag_bhai", "geometry"],
        "sections": [
            ("Full Template", ["shohag_bhai.cpp", "full_template.cpp", "geometry.cpp", "shohag.cpp", "kactl.cpp"]),
        ]
    },
    {
        "chapter": "Miscellaneous",
        "folder_candidates": ["misc", "miscellaneous"],
        "sections": [
            ("Interval Container", ["interval_container.cpp", "intervals.cpp"]),
            ("Efficient Mask Traversal", ["efficient_mask_traversal.cpp", "mask_traversal.cpp"]),
            ("Generationg Permutations", ["generating_permutations.cpp", "generationg_permutations.cpp", "permutations.cpp"]),
            ("Iterating over Submasks", ["iterating_submasks.cpp", "iterating_over_submasks.cpp", "submask.cpp"]),
            ("Random", ["random.cpp", "rng.cpp"]),
            ("Index compression", ["index_compression.cpp", "coordinate_compression.cpp", "compress.cpp"]),
            ("pbds", ["pbds.cpp", "policy_based_data_structures.cpp"]),
            ("Bitset", ["bitset.cpp"]),
            ("Primes", ["primes.cpp"]),
            ("Digit Range Sum", ["digit_range_sum.cpp", "digit_dp.cpp"]),
            ("Custom Hash", ["custom_hash.cpp", "gp_hash_table.cpp"]),
        ]
    }
]

def search_entire_repo(candidate_filenames):
    """Fallback: Search entire directory tree recursively for any matching candidate file."""
    for root, _, files in os.walk(BASE_DIR):
        if ".git" in root or "build" in root:
            continue
        for f in files:
            ext = os.path.splitext(f)[1].lower()
            if ext in VALID_EXTENSIONS or os.path.splitext(f)[0].lower() in candidate_filenames:
                for cand in candidate_filenames:
                    cand_clean = cand.lower().replace("_", "").replace("-", "").replace(".", "")
                    f_clean = f.lower().replace("_", "").replace("-", "").replace(".", "")
                    if cand_clean == f_clean or (len(cand_clean) > 3 and cand_clean in f_clean):
                        return os.path.join(root, f).replace("\\", "/")
    return None

def find_file(folder_candidates, candidate_filenames):
    # 1. Check target folder candidates
    for f_cand in folder_candidates:
        folder_path = os.path.join(BASE_DIR, "code_library", f_cand)
        if not os.path.exists(folder_path):
            continue
        
        dir_files = [f for f in os.listdir(folder_path) if os.path.splitext(f)[1].lower() in VALID_EXTENSIONS or os.path.splitext(f)[0].lower() in candidate_filenames]
        
        for cand in candidate_filenames:
            for actual in dir_files:
                if actual.lower() == cand.lower():
                    return os.path.join(folder_path, actual).replace("\\", "/"), folder_path
        
        for cand in candidate_filenames:
            cand_base = os.path.splitext(cand)[0].lower()
            for actual in dir_files:
                actual_base = os.path.splitext(actual)[0].lower()
                if actual_base == cand_base:
                    return os.path.join(folder_path, actual).replace("\\", "/"), folder_path

        for cand in candidate_filenames:
            clean_cand = os.path.splitext(cand)[0].lower().replace("_", "").replace("-", "").replace(" ", "")
            if len(clean_cand) < 2:
                continue
            for actual in dir_files:
                clean_actual = os.path.splitext(actual)[0].lower().replace("_", "").replace("-", "").replace(" ", "")
                if clean_cand in clean_actual or clean_actual in clean_cand:
                    return os.path.join(folder_path, actual).replace("\\", "/"), folder_path

    # 2. Repo-wide fallback search if not in target folder
    repo_match = search_entire_repo(candidate_filenames)
    if repo_match:
        return repo_match, os.path.dirname(repo_match)

    return None, None

def find_formulae_file():
    """Locate formulae.tex, math.tex, or any TeX file in a formulae directory."""
    for root, _, files in os.walk(BASE_DIR):
        if ".git" in root or "build" in root:
            continue
        for f in files:
            if f.endswith(".tex"):
                f_lower = f.lower()
                root_lower = root.lower()
                if "formula" in f_lower or "math" in f_lower or "formula" in root_lower:
                    return os.path.join(root, f).replace("\\", "/")
    return None

def build_tex():
    lines = []
    total_files = 0

    for item in EXACT_TOC:
        chapter_title = item["chapter"]
        lines.append(f"\\chapter{{{chapter_title}}}")

        for exact_section_title, candidates in item["sections"]:
            matched_file, folder_path = find_file(item["folder_candidates"], candidates)
            
            lines.append(f"\\section{{{exact_section_title}}}")
            if matched_file:
                ext = os.path.splitext(matched_file)[1].lower()
                if ext == ".tex":
                    lines.append(f"\\input{{{matched_file}}}")
                elif ext in {".json", ".txt", ".sublime-snippet", ".sublime-build", ".sh", ".bash"}:
                    lines.append(f"\\lstinputlisting[language=bash]{{{matched_file}}}")
                else:
                    lines.append(f"\\lstinputlisting[language=C++]{{{matched_file}}}")
                total_files += 1
            else:
                lines.append(f"% WARNING: File for '{exact_section_title}' not found in repository.")
                print(f"⚠️ Warning: Could not locate file for '{exact_section_title}'.")
            lines.append("")

    # Formulae chapter
    formulae_file = find_formulae_file()
    lines.append("\\chapter{Formulae}")
    if formulae_file:
        lines.append(f"\\input{{{formulae_file}}}")
        total_files += 1
        print(f"✅ Found Formulae section at '{formulae_file}'")
    else:
        lines.append("% WARNING: Formulae file not found in repository.")
        print("⚠️ Warning: Could not find formulae .tex file in repository.")
    lines.append("")

    with open(OUTPUT_TEX, "w", encoding="utf-8") as f:
        f.write("\n".join(lines))

    print(f"✅ Successfully generated '{OUTPUT_TEX}' ({total_files} active files integrated).")

if __name__ == "__main__":
    build_tex()