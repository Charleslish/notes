---
name: cs128-lesson-workflow
description: Process a CS 128 lesson into concise bilingual notes and a locally organized programming activity, then submit and iterate until the course grader explicitly reports 100%.
---

# CS 128 Lesson Workflow

Use this skill when the user gives a CS 128 lesson URL and asks to make notes, prepare its programming activity, solve it, and submit/grade it.

## Workflow

1. **Open the lesson.** Follow the user's browser preference. If none is stated and browser navigation is needed, ask whether to use the in-app browser or Chrome, then use their choice. Read the lesson headings, core explanations, and the full Programming Activity specification, including constraints and starter-file structure.
2. **Make a concise lesson folder.** In the user's existing CS 128 notes directory, copy the established `L1 Hello World` folder as the template. Name the new folder `L<number> <Lesson Name>` (infer the next lecture number from the existing sequence). Remove the copied Hello World source file, rename the copied notes file to match the new lesson, and keep the template's folder conventions. Reuse the shared `Lecture Notes/Makefile` by making each lesson folder Makefile contain `include ../Makefile`; do not copy a custom build recipe unless the user asks. Keep the lesson folder minimal: do not copy `.devcontainer/`, `.vscode/`, `.clang-format`, `.clang-tidy`, or other editor/container/linter settings unless the user explicitly requests them. Remove build products such as executables and `.dSYM` bundles; retain only source, notes, problem text, and needed directory placeholders.
3. **Write notes in the user's format.** In the notes file, retain the lesson's original subsection titles. For each subsection, write short English sentences, one per line, with no bullets or numbering. Prefer key textbook wording with light trimming. Include only essential code examples. In the chat, first explain the central idea in Chinese with a minimal example, then provide the English notes. Skip activity transcripts and routine outputs.
4. **Preserve the assignment locally.** Put the Programming Activity requirements in `src/problem.txt`, clearly including required signatures/behavior, constraints, and permitted headers. Download all provided `.cc` and `.hpp` starter files into the matching `src/` and `includes/` folders. Preserve supplied files and their interfaces.
5. **Implement carefully.** Work through the specification and edge cases; compile locally with the exact course C++ standard and warning flags when available. Keep the implementation readable and satisfy style/lint conventions as well as functional tests. For graded coursework, support the user's learning by explaining the key invariant and reasoning instead of hiding the solution process.
6. **Submit and iterate.** Upload the completed project to the correct course activity, run it if needed, then click Grade. Read every failed rubric item and diagnostic, fix it locally, upload the updated files, and grade again. Do not stop at a successful compile, a high score, a queued job, or an assumed result. Wait for the grader to finish and verify the latest result explicitly says `GRADED (100%)` and all rubric items pass. If the grader is still running, continue checking; report a blocker only when a concrete external problem prevents progress.
7. **Clean and publish the local work.** Remove copied editor/container/linter configuration and compiled artifacts from the new lesson folder unless explicitly requested. Inspect `git status`, confirm the configured remote and branch, and stage only the intended lesson folder and this skill. Follow the repository’s established commit style: make one commit for the lesson, with a specific title in the form `commit L<number> <Lesson Name>` (for example, `commit L37 Arrays Under the Hood`). Avoid abstract generic titles or conventional prefixes such as `docs:` and `fix:` when the repository uses its lesson-title format. Include the skill update in the lesson commit when it belongs to that lesson. Push to the existing repository remote when the user requests it, then verify the push succeeded and the branch is up to date.
8. **Close with a compact explanation.** Summarize the lesson in Chinese with only the main mental model, key trade-off/invariant, and one minimal example when useful. Use a small text diagram or other visual aid only when it materially improves clarity. Keep this much shorter than the lesson. Report the final grade only after verifying 100%, and link the local notes and solution files.

## Completion checklist

- [ ] Lesson folder follows the local template and naming convention.
- [ ] Notes file uses original subsection headings and the requested English line format.
- [ ] `problem.txt` contains the assignment requirements.
- [ ] All starter `.cc` and `.hpp` files are present in the project.
- [ ] Implementation satisfies the specification and compiles with course flags.
- [ ] The lesson Makefile includes `../Makefile`, and no unwanted template configuration or build products remain in the lesson folder.
- [ ] If requested, intended changes are committed and pushed to the configured remote.
- [ ] Course page shows the latest result as `GRADED (100%)`.
- [ ] Final response gives a concise Chinese explanation and links the artifacts.
