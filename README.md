# string-art

String Art Generator - Convert images to thread art patterns with support for multiple colors, optimized thread paths using Beam-Search, and export-ready instructions for physical recreation

# TODO

1. separate string struct //DONE
2. implement draw string // DONE
3. implement greedy (multicolor from initial version)
4. implement cli
5. better Metadata serialisation
6. test metadata
7. test dlls
8. add ssim metric
9. add beam_search solver
10. compare approaches
11. make presentable project (README, ci/cd, docs)
12. add metrics combination operators (+, \*, -, /, ^)
13. add image binding to metrics
14. add dynamic metrics (optimized recalculation (let them draw lines by themself))
15. add tools to cli like:
    - follow instruction
    - generate image from instruction
16. add web interface
