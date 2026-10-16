# Theater screen

The web screen for saved films. It goes into ElDewrito's UI folder:

- copy `theater/` to `<game>/ui/screens/theater/`
- add this entry to the `screens` array in `<game>/ui/screens/screens.json`:

```json
{
	"id": "theater",
	"url": "dew://screens/theater/",
	"captureInput": true,
	"zIndex": 2
}
```

`Film.Menu` or the Home key opens it.
