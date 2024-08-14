// The project function defines how your document looks.
// It takes your content and some metadata and formats it.
// Go ahead and customize it to your liking!
#let project(
  title: "",
  authors: (),
  date: none,
  organisation: none,
  logo: none,
  body,
) = {
  // Set the document's basic properties.
  set document(author: authors.map(a => a.name), title: title)
  set page(numbering: "1", number-align: start)
  set text(font: "New Computer Modern", lang: "ca")
  show math.equation: set text(weight: 400)

  // Set paragraph spacing.
  show par: set block(above: 1.2em, below: 1.2em)

  set heading(numbering: "1.1.")

  // Set run-in subheadings, starting at level 4.
  show heading: it => {
    if it.level > 3 {
      parbreak()
      text(11pt, style: "italic", weight: "regular", it.body + ".")
    } else {
      it
    }
  }

  set par(leading: 0.75em)

  // Title page.
  // The page can contain a logo if you pass one with `logo: "logo.png"`.
  v(0.2fr)
  if logo != none {
    align(right, image(logo, width: 100%))
  }
  v(5fr)

  text(1.1em, date)
  v(1.2em, weak: true)
  text(2em, weight: 700, title)
  
  linebreak()
  
  if organisation != none {
    text(organisation)
  }

  // Author information.
  pad(
    top: 0.7em,
    right: 20%,
    grid(
      columns: (50% + 1cm,) * calc.min(2, authors.len()),
      gutter: 1em,
      ..authors.map(author => align(start)[
        *#author.name* \
        #author.year \
        #author.email
      ]),
    ),
  )

  

  v(2.4fr)
  pagebreak()


  // Table of contents.
  outline(title: "Taula de continguts", depth: 3, indent: true)
  pagebreak()


  // Main body.
  set par(justify: true)

  body
}