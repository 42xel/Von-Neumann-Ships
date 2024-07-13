# FAQ
## Why natural indentation ?
If you delved into the code, you'll see that I am not using the usual reversed recursive indentation. If you want to contribute to this project, use whatever style you like, I'll have my ways to format your code (and I'm assuming you have yours to format mine).

But first, what are natural indentation, and recursive indentation ?

Common scriptures (ancient, word, pdf, markdown, ...) use antural indentation, where the bulk of the text is not indented, and important info are indented. For example, titles will be centered, subtitles will be indented, as well as the beginnign of every paragraph.

Most programming scriptures (code) use reversed recursive indentation. Information is hierarchised in a tree-like structure, and indentation materialises nesting.

Here is a list of there respective merits :
- Recursive indentation allows for arbitrarily long nesting, which are simply impossible with its natural counterpart. Since deep nesting is evil, this is a point for natural indentation.
- Natural indentation is much superior for multi-line strings. The leading spaces you get from recursive indentation are about never desirable. Some languages get rid of them for you, but sometimes you do want them. With natural indentation, what you sse is what you get for multi-line strings, and they are neither polluted by nor are polluting the indentation.
- Natural indentation lends better toward braceless styles. Braces are hard to parse with the naked eye, and require to use a ruler to see blocks. Fortunately, most code editor nowadays have these rulers integrated. This is a great solution to a non-issue, as braceless style, natural or recursive (but natural moreso), are legible without the need of rulers.
- Braceless style waste less lines without saccrificing anything on readability. Recursive braceless (ala Python) are better than natural braceless on this point.
- Natural indentation can use paragraph indentation to separate ideas, where recursive style would prefer line skip, and Python with its coding whitespaces would require line skip.
- Natural indentation structure is limited, static. It's much easir to write a linter for, and after some getting used to, easier to navigate.

Since I sometimes work on this project from my phone, using termux and rw kakoune. It means two things :
- I have limited screen real estate, and needed a space efficient indentation style;
- I don't have automatic indentation.

## Indentation
The specific rules for indentations I follow are as such :
- functions are indented thrice
- loops are indented twice
- conditions are indented once
- following an end of block (`}`) indentation strictly increases (so as to materialise the end of block)
- a paragraph indentation may be used to separate blocks which do not start with a function, loop or condition.
