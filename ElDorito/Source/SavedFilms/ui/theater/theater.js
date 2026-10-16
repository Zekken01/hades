// The theater screen: a film browser outside of a film, and playback controls while
// one plays. It drives the Film.* commands in SavedFilms/saved_film_manager.cpp.

const SPEEDS = [0.25, 0.5, 1, 2, 4, 8];

let films = [];
let selected = 0;
let status = null;
let statusTimer = null;

function formatTime(seconds) {
    seconds = Math.max(0, Math.floor(seconds));
    const minutes = Math.floor(seconds / 60);
    const rest = seconds % 60;
    return minutes + ':' + (rest < 10 ? '0' : '') + rest;
}

function formatSize(bytes) {
    return bytes >= 1048576 ? (bytes / 1048576).toFixed(1) + ' MB' : Math.ceil(bytes / 1024) + ' KB';
}

function escapeHtml(text) {
    return $('<div>').text(text).html();
}

function modeName(film) {
    if (film.mode === 1)
        return 'Campaign';
    return film.gametype || 'Multiplayer';
}

/* ---------- browser */

async function loadFilms() {
    try {
        films = JSON.parse(await dew.command('Film.ListJson', { internal: true }));
    } catch (e) {
        films = [];
    }
    selected = Math.min(selected, Math.max(0, films.length - 1));
    renderList();
}

function renderList() {
    const list = $('#film_list').empty();
    films.forEach((film, index) => {
        $('<li>')
            .toggleClass('selected', index === selected)
            .append($('<span>').text(film.map))
            .append($('<span class="film_info">').text(modeName(film) + '  ' + formatTime(film.lengthSeconds)))
            .on('click', () => select(index))
            .on('dblclick', () => { select(index); playSelected(); })
            .appendTo(list);
    });
    $('#film_count').text(films.length === 1 ? '1 FILM' : films.length + ' FILMS');
    renderDetails();
}

function renderDetails() {
    const film = films[selected];
    $('#empty_message').toggle(!film);
    $('.details_table').toggle(!!film);
    $('#details_map').text(film ? film.map : '');
    $('#details_gametype').text(film ? modeName(film) : '');
    if (!film)
        return;
    $('#details_length').text(formatTime(film.lengthSeconds));
    $('#details_date').text(new Date(film.modified * 1000).toLocaleString());
    $('#details_size').text(formatSize(film.size));
    $('#details_name').text(film.name);
}

function select(index) {
    if (!films.length)
        return;
    selected = (index + films.length) % films.length;
    renderList();
    const item = $('#film_list li')[selected];
    if (item)
        item.scrollIntoView({ block: 'nearest' });
}

function playSelected() {
    const film = films[selected];
    if (!film)
        return;
    dew.command('Film.Play "' + film.name + '"').then(() => dew.hide()).catch(error => dew.toast({ body: escapeHtml(String(error)) }));
}

function deleteSelected() {
    const film = films[selected];
    if (!film)
        return;
    dew.command('Film.Delete "' + film.name + '"').then(loadFilms).catch(error => dew.toast({ body: escapeHtml(String(error)) }));
}

/* ---------- playback controls */

async function refreshStatus() {
    try {
        status = JSON.parse(await dew.command('Film.Status', { internal: true }));
    } catch (e) {
        return;
    }

    const playing = status.playing;
    $('body').toggleClass('playing', playing).toggleClass('browsing', !playing);
    if (!playing)
        return;

    const rate = status.tickRate || 60;
    const current = Math.min(status.tick, status.length);
    $('#controls_name').text(status.name);
    $('#time_current').text(formatTime(current / rate));
    $('#time_length').text(formatTime(status.length / rate));
    $('#progress_fill').css('width', (status.length ? 100 * current / status.length : 0) + '%');

    let state = status.ended ? 'Ended' : status.speed === 0 ? 'Paused' : status.speed + 'x';
    $('#controls_state').text(state);
    $('#pause_label').text(status.speed === 0 ? 'Play' : 'Pause');
}

function togglePause() {
    dew.command('Film.Pause').then(refreshStatus);
}

function changeSpeed(direction) {
    if (!status)
        return;
    let index = SPEEDS.indexOf(status.speed);
    if (index < 0)
        index = SPEEDS.indexOf(1);
    index = Math.max(0, Math.min(SPEEDS.length - 1, index + direction));
    dew.command('Film.Speed ' + SPEEDS[index]).then(refreshStatus);
}

function endFilm() {
    dew.command('Film.End').then(() => dew.hide());
}

/* ---------- screen */

function closeTheater() {
    dew.hide();
}

// Arrows, Enter/Space (A) and Escape (B) come through dew.input like a controller;
// these are the keys it does not cover.
function onKeyDown(e) {
    const playing = status && status.playing;
    switch (e.key) {
        case 'Home':
            closeTheater();
            break;
        case 'Delete':
            if (!playing) deleteSelected();
            break;
        case 'e':
        case 'E':
            if (playing) endFilm();
            break;
        default:
            return;
    }
    e.preventDefault();
}

dew.input.on('action', function (e) {
    const playing = status && status.playing;
    switch (e.action) {
        case dew.input.Actions.A:
            playing ? togglePause() : playSelected();
            break;
        case dew.input.Actions.B:
            closeTheater();
            break;
        case dew.input.Actions.X:
            if (!playing) deleteSelected();
            break;
        case dew.input.Actions.Y:
            if (playing) endFilm();
            break;
        case dew.input.Actions.LeftBumper:
            if (playing) changeSpeed(-1);
            break;
        case dew.input.Actions.RightBumper:
            if (playing) changeSpeed(1);
            break;
    }
});

// type 0/1 is the D-pad, stick or arrow keys (axis 0 vertical, 1 horizontal).
dew.input.on('scroll', function (type, axis, value) {
    if (type === 2)
        return;
    if (status && status.playing) {
        if (axis === 1)
            changeSpeed(value);
    } else if (axis === 0) {
        select(selected + value);
    }
});

dew.on('show', async function () {
    window.addEventListener('keydown', onKeyDown);
    await refreshStatus();
    if (!status || !status.playing)
        await loadFilms();
    statusTimer = setInterval(refreshStatus, 250);
});

dew.on('hide', function () {
    window.removeEventListener('keydown', onKeyDown);
    clearInterval(statusTimer);
    statusTimer = null;
    dew.input.reset();
});
